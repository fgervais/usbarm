/*
 * Usb.cpp
 *
 *  Created on: 2009-09-29
 *      Author: oex
 */

#include "Usb.h"
#include "MAX3421E.h"
#include "GpioPin.h"
#include "GpioPinConfiguration.h"
#include "Gpio.h"
#include "TimerConfiguration.h"
#include "Timer.h"
#include "ControlRequest.h"
#include "GetDescriptor.h"
#include "SetAddress.h"
#include "SetConfiguration.h"
#include "DeviceDescriptor.h"
#include "OutputReport.h"
#include "GamepadOutputReport.h"
#include "GamepadInputReport.h"
#include "GamepadReportListener.h"

#include <stdint.h>

/**
 * Interface to MAX3421E controller.
 *
 * Copyright note: A lot of this code is coming from MAXIM USB Lab sample code.
 * Not literally but the sequence is greatly inspired. Following is an exact copy
 * of their code license :
 *
 *******************************************************************************
 *
 * Copyright (C) 2006 Maxim Integrated Products, Inc. All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL MAXIM
 * INTEGRATED PRODUCTS INC. BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR
 * IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 *******************************************************************************
 *
 * Subnote: I was really *not* impressed by the quality of the code included
 * in the USB Lab. It is weird that Maxim release that kind of code. Francois
 *
 * @param controller instance of the MAX3421E controller
 * @param interruptPin Pin which is used by the MAX3421E to interrupt the CPU
 */
Usb::Usb(MAX3421E *controller, GpioPin *interruptPin, Timer* timer) {
	this->controller = controller;
	this->interruptPin = interruptPin;
	this->timer = timer;

	// Init class members
	gamepadReport = 0;
	devDetected = 0;
	devEnumerated = 0;
	serviceRequired = 0;
	serviceInitialized = 0;
	state = Disconnect;

	// Ensure the external interrupt pin has the right configuration
	GpioPinConfiguration gpioPinconfig;
	gpioPinconfig.pin = Gpio::PULLUP_PULLDOWN_INPUT;
	interruptPin->configure(gpioPinconfig);

	/*
	 * Configure the Timer in counter mode
	 *
	 * Ok, there is some things that needs to be explained here.
	 * First I take into account that I'll receive a general
	 * purpose timer (TIM2 to TIM5). Furthermore, I assume that
	 * APB1 prescaler is 2 so that the timer has an input clock
	 * of 36 Mhz.
	 *
	 * For more information on what I'm going to say next, you can
	 * look at in the STM32 reference manual chapter Clocks in
	 * Reset and clock control (RCC).
	 *
	 * It is stated in the manual that if the APB1 prescaler is not 1,
	 * the clock of the timer will be multiplied by two. In our case
	 * The input clock is 36 Mhz so the timer2 is actually running at
	 * 72 Mhz.
	 *
	 * In that case, the time taken by the timer to overflow can be
	 * calculated that way :
	 *
	 * 1/(72 * 10^6) * ('prescaler' + 1) * 'auto reload'
	 *
	 * Keyboard interrupt = 24 ms
	 * 1/(72 * 10^6) * (29 + 1) * 57600 = 24 ms
	 *
	 * Gamepad interrupt = 1 ms
	 * 1/(72 * 10^6) * (1 + 1) * 36000 = 1 ms
	 */
	TimerConfiguration timerConfig;
	timerConfig.mode = Timer::COUNTER_MODE;
	timerConfig.autoReload = 36000;
	timerConfig.prescaler = 1;
	//debug
	//timerConfig.autoReload = 0xFFFF;
	//timerConfig.prescaler = 1500;
	timer->configure(timerConfig);

	// TODO: Change this for the "standard" configuration
	/* Configure the controller */
	controller->configure();
	controller->reset();

	// Register as an external interrupt listener
	interruptPin->addEventListener(this);
}

Usb::~Usb() {

}

void Usb::listenForDevice() {
	/*
	 * Configure the driver as a host with a pull-down on each data line.
	 * The host is running at full speed.
	 *
	 * Pull-down are needed to detect a new device and the speed supported
	 * by that device. A low speed device will have a pull-up on D- and
	 * a full speed device a pull-up on D+.
	 */
	controller->writeRegister(MAX3421E::MODE,
			MAX3421E::MODE_DPPULLDN | MAX3421E::MODE_DMPULLDN | MAX3421E::MODE_HOST);

	state = Disconnect;

	// Clear the connect IRQ
	controller->writeRegister(MAX3421E::HIRQ, MAX3421E::HIRQ_CONNIRQ);
	// Enable connect interrupt
	controller->writeRegister(MAX3421E::HIEN, MAX3421E::HIEN_CONNIE);
	// Enable global interrupt
	controller->writeRegister(MAX3421E::CPUCTL, MAX3421E::CPUCTL_IE);

	// Perform a bus reset (Put the bus in SE0 state)
	// Trick used to detect a device already plugged in
	controller->writeRegister(MAX3421E::HCTL, MAX3421E::HCTL_BUSRST);
}

void Usb::enumerateDevice() {
	ControlRequest* request;
	uint8_t* rawData;

	/*
	 * Host and device use this first reset to issue the high speed handshake.
	 *
	 * We have to do it even if we know that our controller doesn't support
	 * high speed since it's in the USB standard.
	 */
	busReset();

	/*
	 * According to the programming manual we should wait at least 1 frame
	 *
	 * Maxim's example use 200. It shouldn't hurt to wait a little longer.
	 */
	waitFrames(200);

	/*
	 * Get the maximum packet size of EndPoint 0.
	 *
	 * This information will be used for every other control transfers.
	 * For those how are not familiar with the USB standard, the device
	 * will respond to address 0x00 until we give it another one.
	 */
	controller->writeRegister(MAX3421E::PERADDR, 0x00);

	// Using the 'safe' value for now
	maxPacketSize = 0x08;

	request = new GetDescriptor(0x0100, 0x0008);
	controller->writeRegister(MAX3421E::HCTL, MAX3421E::HCTL_SNDTOG1);
	sendRequest(request);

	rawData = new uint8_t[request->wLength];
	controller->writeRegister(MAX3421E::HCTL, MAX3421E::HCTL_RCVTOG1);
	receiveRawData(rawData, request->wLength, 0x00, maxPacketSize);

	// OUT Status stage
	launchTransfer(MAX3421E::TOKEN_HSOUT, 0x00);

	// Set the maximum EP0 packet size
	maxPacketSize = rawData[7];

	// Free resources used for that request
	delete request;
	delete[] rawData;

	// Reset the device to be in a known state
	busReset();
	waitFrames(200);

	/*
	 * Set address of the device.
	 */
	request = new SetAddress(0x07);
	controller->writeRegister(MAX3421E::HCTL, MAX3421E::HCTL_SNDTOG1);
	sendRequest(request);

	/*
	 * The status stage should always be in the opposite direction of the last
	 * transaction. As there is not Data Stage, the last transaction was in the
	 * OUT direction so the Status Stage send an IN token.
	 * We should get NAK or the DATA1 PID. When we get the DATA1 PID the 3421
	 * automatically sends the closing ACK.
	 */
	launchTransfer(MAX3421E::TOKEN_HSIN, 0x00);

	// From MAXIM USB Lab
	waitFrames(30);
	// Further communication should be sent to address 0x07
	controller->writeRegister(MAX3421E::PERADDR, 0x07);

	// Free resources used for that request
	delete request;

	// TODO: Change this to use the request variable defined in that function
	// Play with descriptors
	ControlRequest* r = new GetDescriptor(0x0100, 0x0012);
	sendRequest(r);

	rawData = new uint8_t[r->wLength];
	controller->writeRegister(MAX3421E::HCTL, MAX3421E::HCTL_RCVTOG1);
	receiveRawData(rawData, r->wLength, 0x00, maxPacketSize);

	// OUT Status stage
	launchTransfer(MAX3421E::TOKEN_HSOUT, 0x00);

	DeviceDescriptor* deviceDescriptor = new DeviceDescriptor(rawData);

	devEnumerated = 1;

	// debug
	//if(deviceDescriptor->idVendor == 0x04b3) { // Keyboard
	//if(deviceDescriptor->idVendor == 0x046d) { // Mouse
	//if(deviceDescriptor->idVendor == 0x045e) { // Xbox receiver
		//if(deviceDescriptor->idProduct == 0x3025) { // Keyboard
		//if(deviceDescriptor->idProduct == 0xc018) { // Mouse
		//if(deviceDescriptor->idProduct == 0x0719) { // Xbox receiver
			// Blink led fast
			/*GPIOA->BSRR |= 0x01;	// On
			for(uint32_t i=0; i<100000; i++);
			GPIOA->BRR |= 0x01;	// Off
			for(uint32_t i=0; i<100000; i++);*/
		//}
	//}
	delete deviceDescriptor;
}

void Usb::serviceHid() {
	uint8_t rawData[0x1d];
	static uint8_t outPollingDelay = 7;
	uint8_t hrslt = 1;

	if(!serviceInitialized) {
		timer->addEventListener(this);
		timer->enable();
		serviceInitialized = 1;

		ControlRequest* setConfiguration = new SetConfiguration(0x01);
		controller->writeRegister(MAX3421E::HCTL, MAX3421E::HCTL_SNDTOG1);
		sendRequest(setConfiguration);
		delete setConfiguration;

		// Init data toggle for endpoint 0x01
		controller->writeRegister(MAX3421E::HCTL, MAX3421E::HCTL_SNDTOG0);
		controller->writeRegister(MAX3421E::HCTL, MAX3421E::HCTL_RCVTOG0);
	}
	if(serviceRequired) {
		if(outPollingDelay == 0) {
			OutputReport* outputReport = new GamepadOutputReport(0x02);
			sendInterruptReport(outputReport);
			delete outputReport;
			outPollingDelay = 7;
		}
		else {
			outPollingDelay--;
		}

		// Get an interrupt report
		//receiveRawData(rawData, 0x08, 0x01, 0x08); // Keyboard
		//receiveRawData(rawData, 0x04, 0x01, 0x05); // Mouse
		hrslt = receiveRawData(rawData, 0x1d, 0x01, 0x20); // Gamepad

		serviceRequired = 0;

		//debug
		if(hrslt == MAX3421E::HRSLT_SUCCESS) {
			if(rawData[1] == 0x01) {
				delete gamepadReport;
				gamepadReport = new GamepadInputReport(&rawData[4]);

				// Browse through every listeners and tell them that
				// this object have an event pending
				for(int32_t i=0; i<gamepadListeners.size(); i++) {
					if(gamepadListeners.getElement(i) != 0) {
						gamepadListeners.getElement(i)->gamepadReportReceived(this);
					}
				}
			}

		}

	}
}

void Usb::addEventListener(GamepadReportListener* listener) {
	gamepadListeners.addElement(listener);
}

void Usb::waitFrames(uint32_t number) {
	uint8_t frameCounter;
	uint8_t hirq;

	// Wait the specified number of frame
	for(frameCounter = 0; frameCounter < number; frameCounter++) {
		// Clear frame IRQ
		controller->writeRegister(MAX3421E::HIRQ, MAX3421E::HIRQ_FRAMEIRQ);

		do {
			controller->readRegister(MAX3421E::HIRQ, &hirq);
		} while(hirq == 0);

	}

}

uint8_t Usb::sendRequest(ControlRequest* request) {
	// Load setup buffer
	controller->writeBytes(MAX3421E::SUDFIFO,request->toArray(),0x08);

	// TODO: should be able to timeout
	uint8_t hrslt;
	do {
		hrslt = launchTransfer(MAX3421E::TOKEN_SETUP, 0x00);
	} while(hrslt != MAX3421E::HRSLT_SUCCESS);

	return hrslt;
}

uint8_t Usb::receiveRawData(uint8_t* rawData, uint16_t length,
		uint8_t endpoint, uint8_t packetSize) {
	// Variable used to store MAX3421E register value
	uint8_t hrslt;
	uint8_t rcvbc;
	uint16_t offset = 0;

	// First packet has DATA1 ID. See USB standard.
	//controller->writeRegister(MAX3421E::HCTL, MAX3421E::HCTL_RCVTOG1);

	do {
		// Clear the receive IRQ and free the buffer
		controller->writeRegister(MAX3421E::HIRQ, MAX3421E::HIRQ_RCVDAVIRQ);

		hrslt = launchTransfer(MAX3421E::TOKEN_IN, endpoint);

		if(hrslt == MAX3421E::HRSLT_SUCCESS) {
			// Check the number of bytes received
			controller->readRegister(MAX3421E::RCVBC, &rcvbc);

			// Clear the receive IRQ and free the buffer
			controller->writeRegister(MAX3421E::HIRQ, MAX3421E::HIRQ_RCVDAVIRQ);

			if(rcvbc <= (length - offset)) {
				// Fill the buffer
				controller->readBytes(MAX3421E::RCVFIFO, rawData+offset, rcvbc);
			}
			else {
				// Fill the buffer
				controller->readBytes(MAX3421E::RCVFIFO, rawData+offset, length - offset);
			}

			offset += rcvbc;
		}

		// Clear the receive IRQ and free the buffer
		//controller->writeRegister(MAX3421E::HIRQ, MAX3421E::HIRQ_RCVDAVIRQ);

		/*
		 * The transfer is complete under three conditions:
		 * 1. There's been a problem in the transfer.
		 * 2. The device sent a short packet (< packetSize)
		 * 3. 'length' bytes have been transferred.
		 */
	} while(hrslt == MAX3421E::HRSLT_SUCCESS && rcvbc == packetSize && offset < length);

	// Clear IRQ and free the buffer
	controller->writeRegister(MAX3421E::HIRQ, MAX3421E::HIRQ_RCVDAVIRQ);

	return hrslt;
}

uint8_t Usb::sendInterruptReport(OutputReport* outputReport) {
	// Load setup buffer
	controller->writeBytes(MAX3421E::SNDFIFO,outputReport->toArray(),outputReport->length);
	controller->writeRegister(MAX3421E::SNDBC, outputReport->length);

	uint8_t hrslt;
	hrslt = launchTransfer(MAX3421E::TOKEN_BULKOUT, 0x01);

	return hrslt;
}

uint8_t Usb::launchTransfer(uint8_t token, uint8_t endpoint) {
	// Variable used to store MAX3421E register value
	uint8_t hirq;
	uint8_t hrsl, hrslt;

	// Clear the transfer IRQ
	controller->writeRegister(MAX3421E::HIRQ, MAX3421E::HIRQ_HXFRDNIRQ);
	// Start transfer
	controller->writeRegister(MAX3421E::HXFR, token|endpoint);

	// Poll the IRQ to know when transfer is done
	do {
		controller->readRegister(MAX3421E::HIRQ, &hirq);
	} while((hirq & MAX3421E::HIRQ_HXFRDNIRQ) == 0);

	// From MAXIM's example. Is it necessary?
	// Clear the transfer IRQ
	controller->writeRegister(MAX3421E::HIRQ, MAX3421E::HIRQ_HXFRDNIRQ);

	// Get transfer result
	controller->readRegister(MAX3421E::HRSL, &hrsl);
	hrslt = hrsl & 0x0F;

	return hrslt;
}

void Usb::busReset() {
	/*
	 * Disable connection interrupt since after the reset, the condition
	 * for the interrupt will be met but it won't be because of a device
	 * connected but only because the bus returned to its default state.
	 */
	controller->writeRegister(MAX3421E::HIEN, 0x00);

	// Perform a bus reset (Put the bus in SE0 state)
	controller->writeRegister(MAX3421E::HCTL, MAX3421E::HCTL_BUSRST);

	state = Reset;

	// Wait until bus reset is done
	uint8_t hctl;
	do {
		controller->readRegister(MAX3421E::HCTL, &hctl);
	} while(hctl == 1);

	state = Default;
	// Clear the connect IRQ
	controller->writeRegister(MAX3421E::HIRQ, MAX3421E::HIRQ_CONNIRQ);
	// Re-enable the connection interrupt
	controller->writeRegister(MAX3421E::HIEN, MAX3421E::HIEN_CONNIE);
}

void Usb::stateChanged(GpioPin* pin) {
	uint8_t hostIRQ;
	controller->readRegister(MAX3421E::HIRQ, &hostIRQ);

	if(hostIRQ & MAX3421E::HIRQ_CONNIRQ) {

		if(state == Disconnect) {
			// Read the bus state
			uint8_t busState;
			controller->readRegister(MAX3421E::HRSL, &busState);
			// Full speed device
			if(busState & MAX3421E::HRSL_JSTATUS) {
				controller->writeRegister(MAX3421E::MODE,
							MAX3421E::MODE_DPPULLDN | MAX3421E::MODE_DMPULLDN
							| MAX3421E::MODE_SOFKAENAB | MAX3421E::MODE_HOST);
			}
			// Low speed device
			else if(busState & MAX3421E::HRSL_KSTATUS) {
				controller->writeRegister(MAX3421E::MODE,
							MAX3421E::MODE_DPPULLDN | MAX3421E::MODE_DMPULLDN
							| MAX3421E::MODE_SOFKAENAB | MAX3421E::MODE_LOWSPEED
							| MAX3421E::MODE_HOST);
			}
			devDetected = 1;
			devEnumerated = 0;
			state = Connect;
		}
		else {
			// Stop automatic SOF/Keep-Alive generation
			controller->writeRegister(MAX3421E::MODE,
						MAX3421E::MODE_DPPULLDN | MAX3421E::MODE_DMPULLDN | MAX3421E::MODE_HOST);

			devDetected = 0;
			//devEnumerated = 0;	// This seems to create a race condition
			state = Disconnect;
		}

		// Clear the connect IRQ
		controller->writeRegister(MAX3421E::HIRQ, MAX3421E::HIRQ_CONNIRQ);
	}

}

void Usb::timerOverflowed(Timer* timer) {
	serviceRequired = 1;
}

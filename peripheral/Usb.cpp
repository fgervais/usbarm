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
	report = 0;
	devDetected = 0;
	devEnumerated = 0;
	serviceRequired = 0;
	serviceInitialized = 0;

	// Ensure the external interrupt pin has the right configuration
	GpioPinConfiguration gpioPinconfig;
	gpioPinconfig.pin = Gpio::PULLUP_PULLDOWN_INPUT;
	interruptPin->configure(gpioPinconfig);

	// Configure the Timer in counter mode
	TimerConfiguration timerConfig;
	timerConfig.mode = Timer::COUNTER_MODE;
	//timerConfig.autoReload = 57600;
	//timerConfig.prescaler = 15;
	timerConfig.autoReload = 0xFFFF;
	timerConfig.prescaler = 1500;
	timer->configure(timerConfig);

	/*
	 * Keyboard interrupt = 24 ms
	 * 1/(36 * 10^6) * 57600 * 15 = 24 ms
	 *
	 * Gamepad interrupt = 1 ms
	 * 1/(36 * 10^6) * 36000 = 1 ms
	 */

	// TODO: Change this for the "standard" configuration
	/* Configure the controller */
	//controller->configure();
	//controller->reset();

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

	request = new GetDescriptor(0x01, 0x08);
	sendRequest(request);

	rawData = new uint8_t[request->length];
	receiveRawData(rawData, request->length, 0x00, maxPacketSize);

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

	// Play with descriptors
}

void Usb::serviceHid() {
	uint8_t* rawData;

	if(!serviceInitialized) {
		timer->addEventListener(this);
		timer->enable();
		serviceInitialized = 1;
	}
	else if(serviceRequired) {
		rawData = new uint8_t[12];
		// Get an interrupt report
		receiveRawData(rawData, 0x08, 0x01, 0x08);
		serviceRequired = 0;
	}
}

void Usb::waitFrames(uint32_t number) {
	uint8_t frameCounter = number;
	uint8_t hirq;

	// Wait the specified number of frame
	do {
		// Clear frame IRQ
		controller->writeRegister(MAX3421E::HIRQ, MAX3421E::HIRQ_FRAMEIRQ);

		do {
			controller->readRegister(MAX3421E::HIRQ, &hirq);
		} while(hirq == 0);

	} while(--frameCounter > 0);

}

uint8_t Usb::sendRequest(ControlRequest* request) {
	// Load setup buffer
	controller->writeBytes(MAX3421E::SUDFIFO,request->toArray(),8);

	return launchTransfer(MAX3421E::TOKEN_SETUP, 0x00);
}

uint8_t Usb::receiveRawData(uint8_t* rawData, uint16_t length,
		uint8_t endpoint, uint8_t packetSize) {
	// Variable used to store MAX3421E register value
	uint8_t hrslt;
	uint8_t rcvbc;
	uint16_t offset = 0;

	// First packet has DATA1 ID. See USB standard.
	controller->writeRegister(MAX3421E::HCTL, MAX3421E::HCTL_RCVTOG1);

	// Clear the receive IRQ just to make sure
	controller->writeRegister(MAX3421E::HIRQ, MAX3421E::HIRQ_RCVDAVIRQ);

	do {
		hrslt = launchTransfer(MAX3421E::TOKEN_IN, endpoint);

		if(hrslt == MAX3421E::HRSLT_SUCCESS) {
			// Check the number of bytes received
			controller->readRegister(MAX3421E::RCVBC, &rcvbc);

			// Clear the receive IRQ
			// This is really important according to the MAX3421E programming manual
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
		/*
		 * The transfer is complete under three conditions:
		 * 1. There's been a problem in the transfer.
		 * 2. The device sent a short packet (< packetSize)
		 * 3. 'length' bytes have been transferred.
		 */
	} while(hrslt == MAX3421E::HRSLT_SUCCESS && rcvbc == packetSize && offset < length);

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
	} while(hirq == 0);

	// From MAXIM example. Is it necessary?
	// Clear the transfer IRQ
	controller->writeRegister(MAX3421E::HIRQ, MAX3421E::HIRQ_HXFRDNIRQ);

	// Get transfer result
	controller->readRegister(MAX3421E::HRSL, &hrsl);
	hrslt = hrsl & 0x0F;

	return hrsl;
}

void Usb::busReset() {
	// Perform a bus reset (Put the bus in SE0 state)
	controller->writeRegister(MAX3421E::HCTL, MAX3421E::HCTL_BUSRST);

	state = Reset;

	// Wait until bus reset is done
	uint8_t hctl;
	do {
		controller->readRegister(MAX3421E::HCTL, &hctl);
	} while(hctl == 1);

	state = Default;
}

void Usb::stateChanged(GpioPin* pin) {
	uint8_t hostIRQ;
	controller->readRegister(MAX3421E::HIRQ, &hostIRQ);

	// Blink led fast
	GPIOA->BSRR |= 0x01;	// On
	for(uint32_t i=0; i<100000; i++);
	GPIOA->BRR |= 0x01;	// Off
	for(uint32_t i=0; i<100000; i++);

	if(hostIRQ & MAX3421E::HIRQ_CONNIRQ) {

		if(state == Disconnect) {
			// Blink led fast
			GPIOA->BSRR |= 0x01;	// On
			for(uint32_t i=0; i<100000; i++);
			GPIOA->BRR |= 0x01;	// Off
			for(uint32_t i=0; i<100000; i++);

			// Clear the connect IRQ
			controller->writeRegister(MAX3421E::HIRQ, MAX3421E::HIRQ_CONNIRQ);
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
			state = Connect;
		}
		else {
			// Blink led fast
			GPIOA->BSRR |= 0x01;	// On
			for(uint32_t i=0; i<100000; i++);
			GPIOA->BRR |= 0x01;	// Off
			for(uint32_t i=0; i<100000; i++);

			// Clear the connect IRQ
			controller->writeRegister(MAX3421E::HIRQ, MAX3421E::HIRQ_CONNIRQ);
			// Stop automatic SOF/Keep-Alive generation
			controller->writeRegister(MAX3421E::MODE,
						MAX3421E::MODE_DPPULLDN | MAX3421E::MODE_DMPULLDN | MAX3421E::MODE_HOST);

			state = Disconnect;
		}
	}

}

void Usb::timerOverflowed(Timer* timer) {
	serviceRequired = 1;

	// Blink led fast
	GPIOA->BSRR |= 0x01;	// On
	for(uint32_t i=0; i<100000; i++);
	GPIOA->BRR |= 0x01;	// Off
	for(uint32_t i=0; i<100000; i++);
}

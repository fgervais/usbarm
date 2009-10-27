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

#include <stdint.h>

Usb::Usb(MAX3421E *controller, GpioPin *interruptPin) {
	this->controller = controller;
	this->interruptPin = interruptPin;

	// Ensure the external interrupt pin has the right configuration
	GpioPinConfiguration config;
	config.pin = Gpio::PULLUP_PULLDOWN_INPUT;
	interruptPin->configure(config);

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
}

void Usb::enumerateDevice() {
	// Perform a bus reset (Put the bus in SE0 state)
	controller->writeRegister(MAX3421E::HCTL, MAX3421E::HCTL_BUSRST);

	/*
	 * Host and device use this first reset to issue the high speed handshake.
	 *
	 * We have to do it even if we know that our controller doesn't support
	 * high speed since it's in the standard.
	 */

	state = Reset;

	// Wait until bus reset is done
	uint8_t hctl;
	do {
		controller->readRegister(MAX3421E::HCTL, &hctl);
	} while(hctl == 1);

	state = Default;

	/*
	 * According to the programming manual we should wait at least 1 frame
	 *
	 * Maxim's example use 200. It shouldn't hurt to wait a little longer.
	 */
	waitFrames(200);

	/*
	 * Get the maximum packet size of endpoint 0.
	 *
	 * This information will be used for every other control transfers.
	 * For those how are not familiar with the USB standard, the device
	 * will respond to address 0x00 until we give it another one.
	 */
	controller->writeRegister(MAX3421E::PERADDR, 0x00);

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

void Usb::stateChanged(GpioPin* pin) {
	uint8_t hostIRQ;
	controller->readRegister(MAX3421E::HIRQ, &hostIRQ);

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

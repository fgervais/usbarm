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

void Usb::detectDevice() {
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

	state = Reset;

	// Clear the connect IRQ
	controller->writeRegister(MAX3421E::HIRQ, MAX3421E::HIRQ_CONNIRQ);
	// Enable connect interrupt
	controller->writeRegister(MAX3421E::HIEN, MAX3421E::HIEN_CONNIE);
}

void Usb::enumerateDevice() {

}

void Usb::stateChanged(GpioPin* pin) {
	uint8_t busState;
	switch(state) {
	case Reset:
		// Blink led fast
		GPIOA->BSRR |= 0x01;	// On
		for(uint32_t i=0; i<100000; i++);
		GPIOA->BRR |= 0x01;	// Off
		for(uint32_t i=0; i<100000; i++);

		// Clear the connect IRQ
		controller->writeRegister(MAX3421E::HIRQ, MAX3421E::HIRQ_CONNIRQ);
		// Read the bus state
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
		state = Default;
		break;
	case Default:
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

		state = Reset;
		break;
	default:
		break;
	}
}

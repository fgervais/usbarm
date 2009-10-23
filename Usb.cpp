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

	status = Reset;

	// Clear the connect IRQ
	controller->writeRegister(MAX3421E::HIRQ, MAX3421E::HIRQ_CONNIRQ);
	// Enable connect interrupt
	controller->writeRegister(MAX3421E::HIEN, MAX3421E::HIEN_CONNIE);
}

void Usb::stateChanged(GpioPin* pin) {
	switch(status) {
	case Reset:
		break;
	case Connected:
		break;
	}

	GPIOA->BSRR |= 0x01;	// On
	for(uint32_t i=0; i<100000; i++);

	GPIOA->BRR |= 0x01;	// Off
	for(uint32_t i=0; i<100000; i++);
}

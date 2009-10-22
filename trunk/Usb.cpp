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

#include "stm32f10x.h" //debug

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

void Usb::stateChanged(GpioPin* pin) {
	GPIOA->BSRR |= 0x01;	// On
	for(uint32_t i=0; i<100000; i++);

	GPIOA->BRR |= 0x01;	// Off
	for(uint32_t i=0; i<100000; i++);
}

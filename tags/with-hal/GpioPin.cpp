/*
 * GpioPin.cpp
 *
 *  Created on: Oct 2, 2009
 *      Author: fgervais
 */

#include "GpioPin.h"

#include "Gpio.h"

GpioPin::GpioPin(Gpio *port, uint32_t pinNumber) {
	this->port = port;
	this->pinNumber = pinNumber;

}

GpioPin::~GpioPin() {

}



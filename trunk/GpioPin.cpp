/*
 * GpioPin.cpp
 *
 *  Created on: Oct 2, 2009
 *      Author: fgervais
 */

#include "GpioPin.h"

#include "Gpio.h"

GpioPin::GpioPin(Gpio *port, uint32_t pinFlag) {
	this->port = port;
	this->pinFlag = pinFlag;

}

GpioPin::~GpioPin() {
	// TODO Auto-generated destructor stub
}

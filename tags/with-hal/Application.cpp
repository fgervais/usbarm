/*
 * Application.cpp
 *
 *  Created on: 2009-09-29
 *      Author: oex
 */

#include "Microcontroller.h"

#include "Kernel.h"
#include "Gpio.h"
#include "GpioConfiguration.h"

#include <stdint.h>

int main(void) {

	Gpio* gpioA = Kernel::getMicrocontroller()->getGpioA();

	GpioConfiguration config;

	config.pin[0] = GpioConfiguration::OUTPUT;

	gpioA->configure(config);

}

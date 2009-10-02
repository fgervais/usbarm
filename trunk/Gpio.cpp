/*
 * Gpio.cpp
 *
 *  Created on: 2009-09-29
 *      Author: oex
 */

#include "Gpio.h"

#include "stm32f10x.h"
#include "GpioPin.h"
#include "GpioConfiguration.h"

/**
 * @brief Gpio constructor.
 *
 * This function takes care of the individual pins initialization.
 */
Gpio::Gpio() {
	uint32_t flag = 1;
	for(uint8_t i=0; i<16; i++) {
		// Create a new pin with it's corresponding flag.
		gpioPins[i] = new GpioPin(this, flag);
		flag <<= 1;
	}
}

Gpio::~Gpio() {
	// TODO Auto-generated destructor stub
}

void Gpio::configure(GpioConfiguration config) {

}

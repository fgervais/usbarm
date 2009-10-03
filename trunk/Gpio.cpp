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
#include "STM32F103.h"

/**
 * @brief Gpio constructor.
 *
 * This function takes care of the individual pins initialization.
 */
Gpio::Gpio() {
	for(uint8_t i=0; i<16; i++) {
		// Create a new pin with it's corresponding flag.
		gpioPins[i] = new GpioPin(this, i);
	}
}

Gpio::~Gpio() {
	// TODO Auto-generated destructor stub
}

/**
 * @brief	Configure direction of the port.
 * @param	config Configuration that contain direction for each pins.
 */
void Gpio::configure(GpioConfiguration config) {
	direction = 0;
	for(uint8_t i=0; i<16; i++) {
		direction |= config.pin[i]<<i;
	}

	STM32F103::ioctl(this);
}


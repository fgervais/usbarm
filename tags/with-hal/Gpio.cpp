/*
 * Gpio.cpp
 *
 *  Created on: 2009-09-29
 *      Author: oex
 */

#include "Gpio.h"

#include "GpioPin.h"
#include "GpioConfiguration.h"
#include "Kernel.h"

#include <stdint.h>

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

	// On most controller, all pins are input (high impedance) on reset.
	// Asking the microcontroller about it's reset state could be better,
	direction = 0;
}

Gpio::~Gpio() {

}

/**
 * @brief	Configure direction of the port.
 * @param	config Configuration that contains direction for each pins.
 */
void Gpio::configure(GpioConfiguration config) {
	direction = 0;
	for(uint8_t i=0; i<16; i++) {
		direction |= config.pin[i]<<i;
	}

	// Ask the kernel to configure the port
	Kernel::ioctl(this);
}

void Gpio::setInput(GpioPin* pin) {

}

void Gpio::setOutput(GpioPin* pin) {

}

/**
 * @brief	Configure all pins of the port as input.
 */
void Gpio::setAllInput() {
	direction = 0;

	// Ask the kernel to configure the port
	Kernel::ioctl(this);
}

/**
 * @brief	Configure all pins of the port as output.
 */
void Gpio::setAllOutput() {
	direction = 0xFFFF;

	// Ask the kernel to configure the port
	Kernel::ioctl(this);
}

GpioPin* Gpio::getPin(uint8_t number) {
	if(number >= 16) {
		// TODO: Throw an exception
	}
	return gpioPins[number];
}

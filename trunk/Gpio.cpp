/*
 * Gpio.cpp
 *
 *  Created on: 2009-09-29
 *      Author: oex
 */

#include "Gpio.h"

#include "stm32f10x.h"
#include "GpioPin.h"
#include "GpioInitialization.h"

/**
 * @brief Gpio constructor.
 *
 * This function takes care of the individual pins initialization.
 */
Gpio::Gpio(GPIO_TypeDef *gpioRegisters) {
	this->gpioRegisters = gpioRegisters;

	for(uint8_t i=0; i<16; i++) {
		// Create a new pin with it's corresponding flag.
		gpioPins[i] = new GpioPin(this, i);
	}
}

Gpio::~Gpio() {

}

/**
 * @brief	Configure direction of the port.
 * @param	config Configuration that contains direction for each pins.
 */
void Gpio::init(GpioInitialization init) {

}

GpioPin* Gpio::getPin(uint8_t number) {
	if(number < 16) {
		return gpioPins[number];
	}
	return 0;
}

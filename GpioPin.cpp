/*
 * GpioPin.cpp
 *
 *  Created on: Oct 2, 2009
 *      Author: fgervais
 */

#include "GpioPin.h"
#include "GpioPinConfiguration.h"

#include "Gpio.h"

GpioPin::GpioPin(GPIO_TypeDef *gpioRegisters, uint32_t pinNumber) {
	this->gpioRegisters = gpioRegisters;
	this->pinNumber = pinNumber;
}

GpioPin::~GpioPin() {

}

/**
 * @brief	Configure this pin (Direction, Speed..).
 * @param config Configuration if the pin.
 */
void GpioPin::configure(GpioPinConfiguration config) {
	uint32_t configRegister;

	// Use port configuration low
	if(pinNumber < 8) {
		configRegister = gpioRegisters->CRL;
		// Clear the pin configuration
		configRegister &= ~(0x0F << pinNumber);
		configRegister |= config.pin << pinNumber;
		// Apply changes
		gpioRegisters->CRL = configRegister;
	}
	// Use port configuration high
	else {
		configRegister = gpioRegisters->CRH;
		// Clear the pin configuration
		configRegister &= ~(0x0F << (pinNumber%8));
		configRegister |= config.pin << (pinNumber%8);
		// Apply changes
		gpioRegisters->CRH = configRegister;
	}
}

/**
 * @brief	Check if the pin is at the high level.
 * @return	0 if false, true otherwise.
 */
uint32_t GpioPin::isHigh() {
	return gpioRegisters->IDR & (1 << pinNumber);
}

/**
 * @brief	Set the pin to the high level.
 */
void GpioPin::setHigh() {
	gpioRegisters->BSRR |= (1 << pinNumber);
}

/**
 * @brief	Set the pin to the low level.
 */
void GpioPin::setLow() {
	gpioRegisters->BRR |= (1 << pinNumber);
}

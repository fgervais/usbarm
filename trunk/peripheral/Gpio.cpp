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
Gpio::Gpio(GPIO_TypeDef *gpioRegisters, uint8_t id) : Peripheral(id) {
	this->gpioRegisters = gpioRegisters;

	for(uint8_t i=0; i<16; i++) {
		// Create a new pin with it's corresponding pin number.
		gpioPins[i] = new GpioPin(gpioRegisters, i, id);
	}
}

Gpio::~Gpio() {
	/* Free memory */
	delete[] gpioPins;
}

/**
 * @brief	Configure direction of the port.
 * @param	init Initialization object.
 */
void Gpio::configure(GpioConfiguration portConfig) {
	uint32_t configRegister;

	// Port configuration register low
	configRegister = 0;
	for(uint8_t pinNumber=0; pinNumber<8; pinNumber++) {
		configRegister |= (portConfig.pin[pinNumber] << (pinNumber*4));
	}
	gpioRegisters->CRL = configRegister;

	// Port configuration register high
	configRegister = 0;
	for(uint8_t pinNumber=8; pinNumber<16; pinNumber++) {
		configRegister |= (portConfig.pin[pinNumber] << (pinNumber%8)*4);
	}
	gpioRegisters->CRH = configRegister;
}

/**
 * @brief	Return a concrete GpioPin.
 * @param number Number of the pin requested.
 * @return
 */
GpioPin* Gpio::getPin(uint8_t number) {
	if(number < 16) {
		return gpioPins[number];
	}
	return 0;
}

/**
 * @brief	Get current Gpio port value.
 * @return	Value of the Output Data Register.
 */
uint32_t Gpio::getData() {
	return gpioRegisters->ODR;
}

/**
 * @brief	Set a value to the Gpio port.
 * @param data Value of the Input Data Register to set.
 */
void Gpio::setData(uint32_t data) {
	gpioRegisters->IDR = data;
}

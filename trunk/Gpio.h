/*
 * Gpio.h
 *
 *  Created on: 2009-09-29
 *      Author: oex
 */

#ifndef GPIO_H_
#define GPIO_H_

#include "Peripheral.h"

#include "stm32f10x.h"

class GpioInitialization;
class GpioPin;

/**
 * This class represent a general purpose IO port.
 */
class Gpio: public Peripheral {
public:
	Gpio(GPIO_TypeDef *gpioRegisters);
	virtual ~Gpio();

	static const uint8_t SPEED_10MHZ = 0;
	static const uint8_t OUTPUT = 1;

	void init(GpioInitialization init);

	GpioPin* getPin(uint8_t number);

private:
	GPIO_TypeDef *gpioRegisters;

	GpioPin *gpioPins[16];
};

#endif /* GPIO_H_ */

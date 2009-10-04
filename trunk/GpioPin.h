/*
 * GpioPin.h
 *
 *  Created on: Oct 2, 2009
 *      Author: fgervais
 */

#ifndef GPIOPIN_H_
#define GPIOPIN_H_

#include "stm32f10x.h"

/**
 * General purpose IO pin.
 */
class GpioPinConfiguration;

class GpioPin {
public:
	GpioPin(GPIO_TypeDef *gpioRegisters, uint32_t pinNumber);
	virtual ~GpioPin();

	void configure(GpioPinConfiguration config);

	uint32_t isHigh();

	void setHigh();
	void setLow();

private:
	uint32_t pinNumber;
	GPIO_TypeDef *gpioRegisters;
};

#endif /* GPIOPIN_H_ */

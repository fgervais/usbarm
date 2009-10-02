/*
 * Gpio.h
 *
 *  Created on: 2009-09-29
 *      Author: oex
 */

#ifndef GPIO_H_
#define GPIO_H_

#include "Peripheral.h"

class GpioConfiguration;
class GpioPin;

class Gpio: public Peripheral {
public:
	Gpio();
	virtual ~Gpio();

	void configure(GpioConfiguration config);
	void setInput(GpioPin pin);
	void setOutput(GpioPin pin);

private:
	GpioPin* gpioPins[16];
};

#endif /* GPIO_H_ */

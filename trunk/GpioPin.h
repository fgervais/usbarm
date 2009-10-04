/*
 * GpioPin.h
 *
 *  Created on: Oct 2, 2009
 *      Author: fgervais
 */

#ifndef GPIOPIN_H_
#define GPIOPIN_H_

#include "stm32f10x.h"

class Gpio;

class GpioPin {
public:
	GpioPin(Gpio *port, uint32_t pinNumber);
	virtual ~GpioPin();

	void setHigh();
	void setLow();

	void setInput();
	void setOutput();

	Gpio* getPort() { return port; }
	uint8_t getPinNumber() { return pinNumber; }

private:
	uint32_t pinNumber;
	Gpio *port;
};

#endif /* GPIOPIN_H_ */

/*
 * GpioInitialization.h
 *
 *  Created on: Oct 4, 2009
 *      Author: fgervais
 */

#ifndef GPIOINITIALIZATION_H_
#define GPIOINITIALIZATION_H_

#include "stm32f10x.h"

class GpioInitialization {
public:
	GpioInitialization();
	virtual ~GpioInitialization();

	uint8_t pin[16];
};

#endif /* GPIOINITIALIZATION_H_ */

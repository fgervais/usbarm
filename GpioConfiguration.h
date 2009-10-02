/*
 * GpioConfiguration.h
 *
 *  Created on: Oct 2, 2009
 *      Author: fgervais
 */

#ifndef GPIOCONFIGURATION_H_
#define GPIOCONFIGURATION_H_

#include "stm32f10x.h"

class GpioConfiguration {
public:
	GpioConfiguration();
	virtual ~GpioConfiguration();

	uint8_t pin[16];
};

#endif /* GPIOCONFIGURATION_H_ */

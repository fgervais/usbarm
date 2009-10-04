/*
 * GpioConfiguration.h
 *
 *  Created on: Oct 2, 2009
 *      Author: fgervais
 */

#ifndef GPIOCONFIGURATION_H_
#define GPIOCONFIGURATION_H_

#include <stdint.h>

class GpioConfiguration {
public:
	GpioConfiguration();
	virtual ~GpioConfiguration();

	static const uint8_t INPUT = 0;
	static const uint8_t OUTPUT = 1;

	uint8_t pin[16];
};

#endif /* GPIOCONFIGURATION_H_ */

/*
 * GpioConfiguration.h
 *
 *  Created on: Oct 4, 2009
 *      Author: fgervais
 */

#ifndef GPIOCONFIGURATION_H_
#define GPIOCONFIGURATION_H_

#include <stdint.h>

class GpioConfiguration {
public:
	GpioConfiguration();
	GpioConfiguration(uint8_t defaultConfig);
	virtual ~GpioConfiguration();

	uint8_t pin[16];
};

#endif /* GPIOCONFIGURATION_H_ */

/*
 * GpioPinConfiguration.h
 *
 *  Created on: Oct 4, 2009
 *      Author: fgervais
 */

#ifndef GPIOPINCONFIGURATION_H_
#define GPIOPINCONFIGURATION_H_

#include <stdint.h>

class GpioPinConfiguration {
public:
	GpioPinConfiguration();
	virtual ~GpioPinConfiguration();

	uint8_t pin;
};

#endif /* GPIOPINCONFIGURATION_H_ */

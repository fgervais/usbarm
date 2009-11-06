/*
 * TimerConfiguration.h
 *
 *  Created on: Nov 6, 2009
 *      Author: fgervais
 */

#ifndef TIMERCONFIGURATION_H_
#define TIMERCONFIGURATION_H_

#include "stdint.h"

class TimerConfiguration {
public:
	uint16_t mode;
	uint16_t prescaler;
	uint16_t autoRelead;

	TimerConfiguration();
	virtual ~TimerConfiguration();
};

#endif /* TIMERCONFIGURATION_H_ */

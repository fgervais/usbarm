/*
 * SpiConfiguration.h
 *
 *  Created on: Oct 13, 2009
 *      Author: fgervais
 */

#ifndef SPICONFIGURATION_H_
#define SPICONFIGURATION_H_

#include <stdint.h>

class SpiConfiguration {
public:
	SpiConfiguration();
	virtual ~SpiConfiguration();

	uint16_t lineMode;
	uint16_t frameFormat;
	uint16_t slaveSelect;
	uint16_t firstBit;
	uint16_t prescaler;
	uint16_t configuration;
	uint16_t clockPolarity;
	uint16_t clockPhase;
};

#endif /* SPICONFIGURATION_H_ */

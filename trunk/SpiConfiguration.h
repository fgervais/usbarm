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

	uint16_t bus;
	uint16_t mode;
	uint16_t clockPolarity;
	uint16_t clockPhase;
	uint16_t frameFormat;
	uint16_t firstBit;
};

#endif /* SPICONFIGURATION_H_ */

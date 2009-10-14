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

	uint32_t duplex;
	uint32_t mode;
};

#endif /* SPICONFIGURATION_H_ */

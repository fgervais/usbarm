/*
 * GpioConfiguration.cpp
 *
 *  Created on: Oct 2, 2009
 *      Author: fgervais
 */

#include "GpioConfiguration.h"

#include <stdint.h>

GpioConfiguration::GpioConfiguration() {
	for(uint8_t i=0; i<16; i++) {
		// Initialize every pin as input
		pin[i] = 0;
	}

}

GpioConfiguration::~GpioConfiguration() {
	// TODO Auto-generated destructor stub
}

/*
 * GpioConfiguration.cpp
 *
 *  Created on: Oct 4, 2009
 *      Author: fgervais
 */

#include "GpioConfiguration.h"

GpioConfiguration::GpioConfiguration() {
	// Initialize array
	for(uint8_t i=0; i<16; i++) {
		pin[i] = 0;
	}
}

GpioConfiguration::~GpioConfiguration() {

}

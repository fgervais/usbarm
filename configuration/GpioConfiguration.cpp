/*
 * GpioConfiguration.cpp
 *
 *  Created on: Oct 4, 2009
 *      Author: fgervais
 */

#include "GpioConfiguration.h"

GpioConfiguration::GpioConfiguration() {
	GpioConfiguration(0);
}

GpioConfiguration::GpioConfiguration(uint8_t defaultConfig) {
	// Initialize array
	for(uint8_t i=0; i<16; i++) {
		pin[i] = defaultConfig;
	}
}

GpioConfiguration::~GpioConfiguration() {

}

/*
 * GpioInitialization.cpp
 *
 *  Created on: Oct 4, 2009
 *      Author: fgervais
 */

#include "GpioInitialization.h"

GpioInitialization::GpioInitialization() {
	// Initialize array
	for(uint8_t i=0; i<16; i++) {
		pin[i] = 0;
	}
}

GpioInitialization::~GpioInitialization() {

}

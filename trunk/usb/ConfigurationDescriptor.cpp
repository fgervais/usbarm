/*
 * ConfigurationDescriptor.cpp
 *
 *  Created on: Nov 4, 2009
 *      Author: fgervais
 */

#include "ConfigurationDescriptor.h"

ConfigurationDescriptor::ConfigurationDescriptor(uint8_t* rawDescriptor) {
	length				= rawDescriptor[0];
	descriptorType		= rawDescriptor[1];
	totalLength			= (rawDescriptor[3] << 8) | rawDescriptor[2];
	numInterface		= rawDescriptor[4];
	configurationValue	= rawDescriptor[5];
	configuration		= rawDescriptor[6];
	attributes			= rawDescriptor[7];
	maxPower			= rawDescriptor[8];
}

ConfigurationDescriptor::~ConfigurationDescriptor() {

}

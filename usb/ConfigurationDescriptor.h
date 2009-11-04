/*
 * ConfigurationDescriptor.h
 *
 *  Created on: Nov 4, 2009
 *      Author: fgervais
 */

#ifndef CONFIGURATIONDESCRIPTOR_H_
#define CONFIGURATIONDESCRIPTOR_H_

#include "Descriptor.h"

#include <stdint.h>

class ConfigurationDescriptor: public Descriptor {
public:
	uint8_t length;
	uint8_t descriptorType;
	uint16_t totalLength;
	uint8_t numInterface;
	uint8_t configurationValue;
	uint8_t configuration;
	uint8_t attributes;
	uint8_t maxPower;

	ConfigurationDescriptor(uint8_t* rawDescriptor);
	virtual ~ConfigurationDescriptor();
};

#endif /* CONFIGURATIONDESCRIPTOR_H_ */

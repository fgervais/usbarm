/*
 * DeviceDescriptor.h
 *
 *  Created on: Nov 4, 2009
 *      Author: fgervais
 */

#ifndef DEVICEDESCRIPTOR_H_
#define DEVICEDESCRIPTOR_H_

#include "Descriptor.h"

#include <stdint.h>

class DeviceDescriptor: public Descriptor {
public:
	uint8_t length;
	uint8_t descriptorType;
	uint16_t usb;
	uint8_t deviceClass;
	uint8_t deviceSubClass;
	uint8_t deviceProtocol;
	uint8_t maxPacketSize;
	uint16_t idVendor;
	uint16_t idProduct;
	uint16_t device;
	uint8_t manufacturer;
	uint8_t product;
	uint8_t serialNumber;
	uint8_t numConfigurations;

	DeviceDescriptor(uint8_t* rawDescriptor);
	virtual ~DeviceDescriptor();
};

#endif /* DEVICEDESCRIPTOR_H_ */

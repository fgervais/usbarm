/*
 * DeviceDescriptor.cpp
 *
 *  Created on: Nov 4, 2009
 *      Author: fgervais
 */

#include "DeviceDescriptor.h"

DeviceDescriptor::DeviceDescriptor(uint8_t* rawDescriptor) {
	length			= rawDescriptor[0];
	descriptorType	= rawDescriptor[1];
	usb				= (rawDescriptor[3] << 8) | rawDescriptor[2];
	deviceClass		= rawDescriptor[4];
	deviceSubClass	= rawDescriptor[5];
	deviceProtocol	= rawDescriptor[6];
	maxPacketSize	= rawDescriptor[7];
	idVendor		= (rawDescriptor[9] << 8) | rawDescriptor[8];
	idProduct		= (rawDescriptor[11] << 8) | rawDescriptor[10];
	device			= (rawDescriptor[13] << 8) | rawDescriptor[12];
	manufacturer	= rawDescriptor[14];
	product			= rawDescriptor[15];
	serialNumber	= rawDescriptor[16];
	numConfigurations = rawDescriptor[17];
}

DeviceDescriptor::~DeviceDescriptor() {

}

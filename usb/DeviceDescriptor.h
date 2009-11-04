/*
 * DeviceDescriptor.h
 *
 *  Created on: Nov 4, 2009
 *      Author: fgervais
 */

#ifndef DEVICEDESCRIPTOR_H_
#define DEVICEDESCRIPTOR_H_

#include "Descriptor.h"

class DeviceDescriptor: public Descriptor {
public:
	DeviceDescriptor();
	virtual ~DeviceDescriptor();
};

#endif /* DEVICEDESCRIPTOR_H_ */

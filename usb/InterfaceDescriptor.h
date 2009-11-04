/*
 * InterfaceDescriptor.h
 *
 *  Created on: Nov 4, 2009
 *      Author: fgervais
 */

#ifndef INTERFACEDESCRIPTOR_H_
#define INTERFACEDESCRIPTOR_H_

#include "Descriptor.h"

#include <stdint.h>

class InterfaceDescriptor: public Descriptor {
public:
	InterfaceDescriptor(uint8_t* rawDescriptor);
	virtual ~InterfaceDescriptor();
};

#endif /* INTERFACEDESCRIPTOR_H_ */

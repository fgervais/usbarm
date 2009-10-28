/*
 * GetDescriptor.h
 *
 *  Created on: Oct 28, 2009
 *      Author: fgervais
 */

#ifndef GETDESCRIPTOR_H_
#define GETDESCRIPTOR_H_

#include "ControlPacket.h"

class GetDescriptor: public ControlPacket {
public:
	GetDescriptor(uint16_t descriptorTypeIndex, uint16_t descriptorLength);
	virtual ~GetDescriptor();
};

#endif /* GETDESCRIPTOR_H_ */

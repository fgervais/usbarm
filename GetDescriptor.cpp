/*
 * GetDescriptor.cpp
 *
 *  Created on: Oct 28, 2009
 *      Author: fgervais
 */

#include "GetDescriptor.h"

GetDescriptor::GetDescriptor(uint16_t descriptorTypeIndex, uint16_t descriptorLength) {
	// Set all the Base class member
	requestType	= 0x80;
	request		= 0x06;
	value		= descriptorTypeIndex;
	index		= 0x00;
	length		= 0x00;
}

GetDescriptor::~GetDescriptor() {

}

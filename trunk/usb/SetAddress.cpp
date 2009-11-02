/*
 * SetAddress.cpp
 *
 *  Created on: Oct 28, 2009
 *      Author: fgervais
 */

#include "SetAddress.h"

SetAddress::SetAddress(uint16_t address) {
	// Set all the Base class member
	requestType	= 0x00;
	request		= 0x05;
	value		= address;
	index		= 0x00;
	length		= 0x00;
}

SetAddress::~SetAddress() {

}

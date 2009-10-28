/*
 * ControlPacket.cpp
 *
 *  Created on: Oct 27, 2009
 *      Author: fgervais
 */

#include "ControlPacket.h"

#include <stdint.h>

ControlPacket::ControlPacket(uint8_t request) {
	this->request = request;

	switch(request) {
	case SETADDRESS:
		rawPacket[0] = 0x00;
		rawPacket[1] = request;
		break;
	case GETDESCRIPTOR:
		break;
	default:
		// TODO: Throw an exception?
		break;
	}
}

ControlPacket::~ControlPacket() {

}

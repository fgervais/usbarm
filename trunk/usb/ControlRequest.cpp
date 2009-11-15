/*
 * ControlPacket.cpp
 *
 *  Created on: Oct 27, 2009
 *      Author: fgervais
 */

#include "ControlRequest.h"

#include <stdint.h>

ControlRequest::ControlRequest() {

}

ControlRequest::~ControlRequest() {

}

uint8_t* ControlRequest::toArray() {
	// TODO: I don't think it's safe to return an array like that
	// The array should be allocated using new.
	rawPacket[0] = bmRequestType;
	rawPacket[1] = bRequest;
	rawPacket[2] = (uint8_t)(wValue & 0x00FF);
	rawPacket[3] = (uint8_t)((wValue >> 8) & 0x00FF);
	rawPacket[4] = (uint8_t)(wIndex & 0x00FF);
	rawPacket[5] = (uint8_t)((wIndex >> 8) & 0x00FF);
	rawPacket[6] = (uint8_t)(wLength & 0x00FF);
	rawPacket[7] = (uint8_t)((wLength >> 8) & 0x00FF);

	return rawPacket;
}

/*
 * ControlPacket.h
 *
 *  Created on: Oct 27, 2009
 *      Author: fgervais
 */

#ifndef CONTROLPACKET_H_
#define CONTROLPACKET_H_

#include "UsbPacket.h"

#include <stdint.h>

class ControlPacket: public UsbPacket {
public:
	uint8_t requestType;
	uint8_t request;
	uint16_t value;
	uint16_t index;
	uint16_t length;

	uint8_t* toArray();

	ControlPacket();
	virtual ~ControlPacket();

private:
	uint8_t rawPacket[8];
};

#endif /* CONTROLPACKET_H_ */

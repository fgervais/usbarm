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
	static const uint8_t SETADDRESS = 0x05;
	static const uint8_t GETDESCRIPTOR = 0x06;

	void setValue();
	void setIndex();
	void setLength();
	uint8_t* toArray();

	ControlPacket(uint8_t request);
	virtual ~ControlPacket();

private:
	uint8_t rawPacket[8];
	uint8_t request;
};

#endif /* CONTROLPACKET_H_ */

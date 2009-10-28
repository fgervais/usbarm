/*
 * InterruptPacket.h
 *
 *  Created on: Oct 27, 2009
 *      Author: fgervais
 */

#ifndef INTERRUPTPACKET_H_
#define INTERRUPTPACKET_H_

#include "UsbPacket.h"

class InterruptPacket: public UsbPacket {
public:
	InterruptPacket();
	virtual ~InterruptPacket();
};

#endif /* INTERRUPTPACKET_H_ */

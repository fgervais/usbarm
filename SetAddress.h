/*
 * SetAddress.h
 *
 *  Created on: Oct 28, 2009
 *      Author: fgervais
 */

#ifndef SETADDRESS_H_
#define SETADDRESS_H_

#include "ControlPacket.h"

class SetAddress: public ControlPacket {
public:
	SetAddress(uint16_t address);
	virtual ~SetAddress();
};

#endif /* SETADDRESS_H_ */

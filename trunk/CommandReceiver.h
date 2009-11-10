/*
 * CommandReceiver.h
 *
 *  Created on: 2009-09-29
 *      Author: oex
 */

#ifndef COMMANDRECEIVER_H_
#define COMMANDRECEIVER_H_

#include "CommandWriter.h"

class CommandReceiver {
public:
	CommandReceiver();
	void addCommandWriter();
	virtual void receiveCommand() = 0;
	virtual ~CommandReceiver();
};

#endif /* COMMANDRECEIVER_H_ */

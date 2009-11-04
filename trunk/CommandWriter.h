/*
 * CommandWriter.h
 *
 *  Created on: 2009-09-29
 *      Author: oex
 */

#ifndef COMMANDWRITER_H_
#define COMMANDWRITER_H_

#include "PeripheralEventListener.h"
#include "CommandReceiver.h"

class CommandWriter: public PeripheralEventListener {
public:
	CommandWriter();
	virtual ~CommandWriter();
private:
	CommandReceiver *output;
};

#endif /* COMMANDWRITER_H_ */

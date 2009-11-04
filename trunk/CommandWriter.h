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
#include "Command.h"

class CommandWriter: public PeripheralEventListener {
public:
	CommandWriter(CommandReceiver *output);
	void setOutput(CommandReceiver *output);
	void write(Command *command);
	virtual ~CommandWriter();
private:
	CommandReceiver *output;
};

#endif /* COMMANDWRITER_H_ */

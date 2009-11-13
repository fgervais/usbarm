/*
 * CommandWriter.h
 *
 *  Created on: 2009-09-29
 *      Author: oex
 */

#ifndef COMMANDWRITER_H_
#define COMMANDWRITER_H_

#include "PeripheralEventListener.h"
#include "Mux.h"
#include "Command.h"

class CommandWriter: public PeripheralEventListener {
public:
	CommandWriter();
	void setOutput();
	void write(Command *command);
	virtual ~CommandWriter();
private:
	Mux *output;
};

#endif /* COMMANDWRITER_H_ */

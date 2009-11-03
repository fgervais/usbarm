/*
 * CommandFactory.h
 *
 *  Created on: 2009-09-29
 *      Author: oex
 */
#include "Uart.h"
#include "Pwm.h"
#include "Usb.h"
#include "Command.h"

#ifndef COMMANDFACTORY_H_
#define COMMANDFACTORY_H_

class CommandFactory {
public:
	CommandFactory();
	Command* createCommand(Uart);
	Command* createCommand(Pwm);
	Command* createCommand(Usb);
	virtual ~CommandFactory();
};

#endif /* COMMANDFACTORY_H_ */

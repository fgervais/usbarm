/*
 * CommandFactory.h
 *
 *  Created on: 2009-09-29
 *      Author: oex
 */
#include "Uart.h"
#include "Timer.h"
#include "Usb.h"
#include "Command.h"
#include "stm32f10x.h"

#define COMMAND_MAX_SIZE	12

#ifndef COMMANDFACTORY_H_
#define COMMANDFACTORY_H_

class CommandFactory {
public:
	CommandFactory();
	Command* createCommand(Uart *uart);
	Command* createCommand(Timer *timer);
	Command* createCommand(Usb *usb);
	virtual ~CommandFactory();
private:
	char controllerBuffer[COMMAND_MAX_SIZE];
	char driveBuffer[COMMAND_MAX_SIZE];
	uint8_t controllerIndex;
	uint8_t driveIndex;
};

#endif /* COMMANDFACTORY_H_ */

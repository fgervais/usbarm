/*
 * Command.h
 *
 *  Created on: 2009-09-29
 *      Author: oex
 */

#include "stm32f10x.h"

#ifndef COMMAND_H_
#define COMMAND_H_

class Command {
private:
	char *message;


public:
	Command(char* message, uint8_t size);
	Command(void);
	char* getMessage(void);
	virtual ~Command();
};

#endif /* COMMAND_H_ */

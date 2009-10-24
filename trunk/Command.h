/*
 * Command.h
 *
 *  Created on: 2009-09-29
 *      Author: oex
 */

#ifndef COMMAND_H_
#define COMMAND_H_

class Command {
private:
	char message[10];

public:
	Command(char* message);
	char* getMessage(void);
	virtual ~Command();
};

#endif /* COMMAND_H_ */

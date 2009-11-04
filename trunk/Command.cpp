/*
 * Command.cpp
 *
 *  Created on: 2009-09-29
 *      Author: oex
 */

#include "Command.h"

Command::Command(char* message, uint8_t size) {

	for(uint8_t i = 0; i < size; i++)
	{
		this->message[i] = message[i];
	}

}

Command::Command(){

}

char* Command::getMessage() {
	return message;
}

Command::~Command() {

}

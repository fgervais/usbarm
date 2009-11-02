/*
 * Command.cpp
 *
 *  Created on: 2009-09-29
 *      Author: oex
 */

#include "Command.h"

Command::Command(char* message) {
	this->message = message;

}

char* Command::getMessage() {
	return message;
}

Command::~Command() {

}

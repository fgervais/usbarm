/*
 * CommandFactory.cpp
 *
 *  Created on: 2009-09-29
 *      Author: oex
 */

#include "CommandFactory.h"

Command* CommandFactory::createCommand(Uart) {
	char test[9] = "!B77";
	Command *tmp = new Command(test);
	return tmp;
}
Command* CommandFactory::createCommand(Usb) {
	char test[9] = "!B77";
	Command *tmp = new Command(test);
	return tmp;
}
Command* CommandFactory::createCommand(Pwm) {
	char test[9] = "!B77";
	Command *tmp = new Command(test);
	return tmp;
}

CommandFactory::CommandFactory() {


}

CommandFactory::~CommandFactory() {

}

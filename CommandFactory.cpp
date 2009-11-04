/*
 * CommandFactory.cpp
 *
 *  Created on: 2009-09-29
 *      Author: oex
 */

#include "CommandFactory.h"


Command* CommandFactory::createCommand(Uart *uart) {
	Command *tmpCommand;

	if (uart->getId() == Peripheral::Controller)
	{
		controllerBuffer[controllerIndex] = uart->read();
		if (controllerBuffer[controllerIndex] == '\r')
		{
			tmpCommand = new Command(controllerBuffer, controllerIndex+1);
			controllerIndex = 0;
		}
		else
			controllerIndex++;

	}
	if (uart->getId() == Peripheral::Drive)
	{
		driveBuffer[driveIndex] = uart->read();
		if (driveBuffer[driveIndex] == '\r')
		{
			tmpCommand = new Command(driveBuffer, driveIndex+1);
			driveIndex = 0;
		}
		else
			driveIndex++;
	}


	return tmpCommand;
}
Command* CommandFactory::createCommand(Usb *usb) {
	Command *tmpCommand;
	char test[9] = "!B77";

	tmpCommand = new Command(test,4);
	return new Command(test,4);
}
Command* CommandFactory::createCommand(Pwm *pwm) {
	Command *tmpCommand;
	char test[9] = "!B77";

	tmpCommand = new Command(test,4);
	return new Command(test,4);
}

CommandFactory::CommandFactory() {
	controllerIndex = 0;
	driveIndex = 0;
}

CommandFactory::~CommandFactory() {

}

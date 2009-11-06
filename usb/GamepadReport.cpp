/*
 * GamepadReport.cpp
 *
 *  Created on: Nov 5, 2009
 *      Author: fgervais
 */

#include "GamepadReport.h"

GamepadReport::GamepadReport(uint8_t* rawReport) {
	messageType		= rawReport[0];
	packetSize		= rawReport[1];
	buttons[0]		= rawReport[2];
	buttons[1]		= rawReport[3];
	leftTrigger		= rawReport[4];
	rightTrigger	= rawReport[5];
	LeftStickX		= (rawReport[7] << 8) | rawReport[6];
	LeftStickY		= (rawReport[9] << 8) | rawReport[8];
	rightStickX		= (rawReport[11] << 8) | rawReport[10];
	rightStickY		= (rawReport[13] << 8) | rawReport[12];
}

GamepadReport::~GamepadReport() {

}

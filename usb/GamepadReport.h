/*
 * GamepadReport.h
 *
 *  Created on: Nov 5, 2009
 *      Author: fgervais
 */

#ifndef GAMEPADREPORT_H_
#define GAMEPADREPORT_H_

#include "InterruptReport.h"

#include <stdint.h>

class GamepadReport: public InterruptReport {
public:
	/*
	 * 0x01 : LED status message
	 * 0x00 : normal input report message.
	 */
	uint8_t messageType;
	/*
	 * Should be 20 bytes (0x14)
	 */
	uint8_t packetSize;
	/*
	 * bit (buttons[0])
	 * 0 D-Pad up
	 * 1 D-Pad down
	 * 2 D-Pad left
	 * 3 D-pad right
	 * 4 Start button
	 * 5 Back button
	 * 6 Left stick press
	 * 7 Right stick press
	 *
	 * bit (buttons[1])
	 * 0 Button LB
	 * 1 Button RB
	 * 2 Xbox logo button
	 * 3 Unused
	 * 4 Button A
	 * 5 Button B
	 * 6 Button X
	 * 7 Button Y
	 */
	uint8_t buttons[2];
	uint8_t leftTrigger;
	uint8_t rightTrigger;
	int16_t LeftStickX;
	int16_t LeftStickY;
	int16_t rightStickX;
	int16_t rightStickY;

	GamepadReport(uint8_t* rawReport);
	virtual ~GamepadReport();
};

#endif /* GAMEPADREPORT_H_ */

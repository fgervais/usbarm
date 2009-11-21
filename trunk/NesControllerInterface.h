/*
 * NesControllerInterface.h
 *
 *  Created on: Nov 18, 2009
 *      Author: fgervais
 */

#ifndef NESCONTROLLERINTERFACE_H_
#define NESCONTROLLERINTERFACE_H_

#include "GpioPinEventListener.h"
#include "GamepadReportListener.h"

#include <stdint.h>

class GpioPin;

class NesControllerInterface : public GamepadReportListener, public GpioPinEventListener {
public:
	NesControllerInterface(GpioPin* latch, GpioPin* clock, GpioPin* dataOut);
	virtual ~NesControllerInterface();

	// GpioPinEventListener interface implementation
	void stateChanged(GpioPin* pin);
	// GamepadReportListener interface implementation
	void gamepadReportReceived(Usb* usb);

private:
	GpioPin* latch;
	GpioPin* clock;
	GpioPin* dataOut;

	volatile uint8_t latchedButtons;
	volatile uint8_t currentButtons;
};

#endif /* NESCONTROLLERINTERFACE_H_ */

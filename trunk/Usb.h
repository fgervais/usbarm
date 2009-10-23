/*
 * Usb.h
 *
 *  Created on: 2009-09-29
 *      Author: oex
 */

#ifndef USB_H_
#define USB_H_

#include "Peripheral.h"
#include "GpioPinEventListener.h"

class MAX3421E;
class GpioPin;

class Usb: public Peripheral, GpioPinEventListener {
public:
	Usb(MAX3421E *controller, GpioPin *extInterrupt);
	virtual ~Usb();

	void detectDevice();

	// GpioPinEventListener interface implementation
	void stateChanged(GpioPin* pin);

private:
	MAX3421E *controller;
	GpioPin* interruptPin;

	enum Status { Reset, Connected };

	Status status;
};

#endif /* USB_H_ */

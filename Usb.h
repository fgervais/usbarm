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
class ControlPacket;

class Usb: public Peripheral, GpioPinEventListener {
public:
	Usb(MAX3421E *controller, GpioPin *extInterrupt);
	virtual ~Usb();

	void listenForDevice();
	void enumerateDevice();

	// GpioPinEventListener interface implementation
	void stateChanged(GpioPin* pin);

private:
	MAX3421E *controller;
	GpioPin* interruptPin;

	enum State { Disconnect, Connect, Default, Reset, Normal } state;

	// Global flag
	uint8_t devDetected;
	uint8_t devEnumerated;

	void waitFrames(uint32_t number);
	void sendRequest(ControlPacket request);
	void receiveRawData(uint8_t* rawData);
};

#endif /* USB_H_ */

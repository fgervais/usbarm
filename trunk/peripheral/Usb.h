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
#include "TimerOverflowListener.h"
#include "GamepadInputReport.h"
#include "Vector.h"

class MAX3421E;
class GpioPin;
class Timer;
class ControlRequest;
class GamepadInpputReport;
class OutputReport;
class GamepadReportListener;


class Usb: public Peripheral, public GpioPinEventListener, public TimerOverflowListener {
public:
	Usb(MAX3421E *controller, GpioPin *extInterrupt, Timer* timer);
	virtual ~Usb();

	void listenForDevice();
	void enumerateDevice();
	void serviceHid();
	uint8_t deviceDetected() { return devDetected; };
	uint8_t deviceEnumerated() { return devEnumerated; };
	void addEventListener(GamepadReportListener* listener);
	GamepadInputReport& getGamepadReport() { return *gamepadReport; };

	// GpioPinEventListener interface implementation
	void stateChanged(GpioPin* pin);
	// TimerOverflowListener interface implementation
	void timerOverflowed(Timer* timer);

private:
	MAX3421E *controller;
	GpioPin* interruptPin;
	Timer* timer;
	GamepadInputReport* gamepadReport;
	Vector<GamepadReportListener*> gamepadListeners;

	// Maximum EP0 packet size
	uint8_t maxPacketSize;

	enum State { Disconnect, Connect, Default, Reset, Normal } state;

	// Global flag
	volatile uint8_t devDetected;
	volatile uint8_t devEnumerated;
	volatile uint8_t serviceRequired;
	uint8_t serviceInitialized;

	void waitFrames(uint32_t number);
	uint8_t sendRequest(ControlRequest* request);
	uint8_t receiveRawData(uint8_t* rawData, uint16_t length,
			uint8_t endpoint, uint8_t packetSize);
	uint8_t receiveInterruptReport();
	uint8_t sendInterruptReport(OutputReport* outputReport);
	uint8_t launchTransfer(uint8_t token, uint8_t endpoint);
	void busReset();
};

#endif /* USB_H_ */

/*
 * NesControllerInterface.cpp
 *
 *  Created on: Nov 18, 2009
 *      Author: fgervais
 */

#include "NesControllerInterface.h"
#include "GpioPin.h"
#include "Gpio.h"
#include "GamepadInputReport.h"
#include "GpioPinConfiguration.h"
#include "Usb.h"

NesControllerInterface::NesControllerInterface(GpioPin* clock, GpioPin* latch, GpioPin* dataOut) {
	this->clock = clock;
	this->latch = latch;
	this->dataOut = dataOut;

	latchedButtons = 0;
	currentButtons = 0;

	GpioPinConfiguration pinConfig;

	pinConfig.pin = Gpio::PULLUP_PULLDOWN_INPUT;
	clock->configure(pinConfig);
	clock->setLow();	// set pull-down
	pinConfig.pin = Gpio::PULLUP_PULLDOWN_INPUT;
	latch->configure(pinConfig);
	latch->setLow();	// set pull-down
	pinConfig.pin = Gpio::GP_PUSH_PULL_OUTPUT | Gpio::OUTPUT_SPEED_50MHZ;
	dataOut->configure(pinConfig);

	// Register for Gpio event
	latch->addEventListener(this);
	clock->addEventListener(this);
}

NesControllerInterface::~NesControllerInterface() {

}

void NesControllerInterface::stateChanged(GpioPin* pin) {

	if(pin->getPinNumber() == latch->getPinNumber()) {
		latchedButtons = currentButtons;
	}
	else {
		if((latchedButtons & 0x01)) {
			dataOut->setLow();
		}
		else {
			dataOut->setHigh();
		}

		latchedButtons = latchedButtons >> 1;
	}

}

void NesControllerInterface::gamepadReportReceived(Usb* usb) {
	GamepadInputReport gamepadReport;
	gamepadReport = usb->getGamepadReport();

	if(gamepadReport.back & 0x01) {
		GPIOA->BSRR |= 0x01; // On
	}
	if(!gamepadReport.back & 0x01) {
		GPIOA->BRR |= 0x01;	// Off
	}

	currentButtons = (gamepadReport.x) | (gamepadReport.back << 1) | (gamepadReport.start << 2)
		| (gamepadReport.dPadUp << 3) | (gamepadReport.dPadDown << 4) | (gamepadReport.dPadLeft << 5)
		| (gamepadReport.dPadRight << 6) | (gamepadReport.a << 7);
}

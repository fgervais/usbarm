/*
 * NesControllerInterface.cpp
 *
 *  Created on: Nov 18, 2009
 *      Author: fgervais
 */

#include "NesControllerInterface.h"
#include "GpioPin.h"
#include "GamepadInputReport.h"
#include "Usb.h"

NesControllerInterface::NesControllerInterface(GpioPin* latch, GpioPin* clock, GpioPin* dataOut) {
	this->latch = latch;
	this->clock = clock;
	this->dataOut = dataOut;

	// Register for Gpio event
	latch->addEventListener(this);
	clock->addEventListener(this);
}

NesControllerInterface::~NesControllerInterface() {

}

void NesControllerInterface::stateChanged(GpioPin* pin) {
	if(pin->getPinNumber() == latch->getPinNumber()) {
		latchedButtons = currentButtons;

		if((latchedButtons & 0x01)) {
			dataOut->setHigh();
		}
		else {
			dataOut->setLow();
		}

		latchedButtons = latchedButtons>>1;
	}
	else if(pin->getPinNumber() == clock->getPinNumber()) {
		if((latchedButtons & 0x01)) {
			dataOut->setHigh();
		}
		else {
			dataOut->setLow();
		}

		latchedButtons = latchedButtons>>1;
	}
}

void NesControllerInterface::gamepadReportReceived(Usb* usb) {
	//if(rawData[7] & 0x10) {
	if(usb->getGamepadReport().a) {
		GPIOA->BSRR |= 0x01; // On
	}
	//else if(rawData[7] & 0x20) {
	else if(usb->getGamepadReport().b) {
		GPIOA->BRR |= 0x01;	// Off
	}
}

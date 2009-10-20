/*
 * Usb.cpp
 *
 *  Created on: 2009-09-29
 *      Author: oex
 */

#include "Usb.h"

#include "MAX3421E.h"

Usb::Usb(MAX3421E *controller) {
	this->controller = controller;

	// Configure the controller
}

Usb::~Usb() {

}

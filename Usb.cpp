/*
 * Usb.cpp
 *
 *  Created on: 2009-09-29
 *      Author: oex
 */

#include "Usb.h"
#include "MAX3421E.h"

#include <stdint.h>

Usb::Usb(MAX3421E *controller) {
	this->controller = controller;

	// TODO: Change this for the "standard" configuration
	/* Configure the controller */
	controller->configure();
	controller->reset();
}

Usb::~Usb() {

}

/*
 * Usb.h
 *
 *  Created on: 2009-09-29
 *      Author: oex
 */

#ifndef USB_H_
#define USB_H_

#include "Peripheral.h"

class MAX3421E;

class Usb: public Peripheral {
public:
	Usb(MAX3421E *controller);
	virtual ~Usb();

private:
	MAX3421E *controller;
};

#endif /* USB_H_ */

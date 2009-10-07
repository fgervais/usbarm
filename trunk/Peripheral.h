/*
 * Peripheral.h
 *
 *  Created on: 2009-09-29
 *      Author: oex
 */

#ifndef PERIPHERAL_H_
#define PERIPHERAL_H_

#include "Microcontroller.h"

#include <stdint.h>

class PeripheralEventListener;

class Peripheral {
public:
	Peripheral();
	virtual ~Peripheral();

	uint8_t getId() { return number; }
	void addEventListener(PeripheralEventListener *listener);

private:
	uint8_t number;

protected:
	void notify();
};

#endif /* PERIPHERAL_H_ */

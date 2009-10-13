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
#include "Vector.h"

class PeripheralEventListener;

class Peripheral {
public:
	Peripheral();
	virtual ~Peripheral();

	uint8_t getId() { return id; }
	void addEventListener(PeripheralEventListener *listener);

private:
	uint8_t id;
	Vector<PeripheralEventListener*> listeners;


protected:
	void notify();
};

#endif /* PERIPHERAL_H_ */

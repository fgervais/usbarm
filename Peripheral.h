/*
 * Peripheral.h
 *
 *  Created on: 2009-09-29
 *      Author: oex
 */

#ifndef PERIPHERAL_H_
#define PERIPHERAL_H_

#include "Microcontroller.h"

#include "stm32f10x.h"

class Peripheral: public Microcontroller {
public:
	Peripheral();
	virtual ~Peripheral();

	virtual void handleInterrupt();

	uint8_t getId() { return number; }

private:
	uint8_t number;

protected:
	void notify();
};

#endif /* PERIPHERAL_H_ */

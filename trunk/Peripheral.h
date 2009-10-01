/*
 * Peripheral.h
 *
 *  Created on: 2009-09-29
 *      Author: oex
 */

#ifndef PERIPHERAL_H_
#define PERIPHERAL_H_

#include "Microcontroller.h"

class Peripheral: public Microcontroller {
public:
	Peripheral();
	virtual ~Peripheral();

	void notify();
};

#endif /* PERIPHERAL_H_ */

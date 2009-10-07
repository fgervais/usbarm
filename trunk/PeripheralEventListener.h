/*
 * PeripheralEventListener.h
 *
 *  Created on: 2009-09-29
 *      Author: oex
 */

#ifndef PERIPHERALEVENTLISTENER_H_
#define PERIPHERALEVENTLISTENER_H_

class Peripheral;

class PeripheralEventListener {
public:
	PeripheralEventListener();
	virtual ~PeripheralEventListener();

	virtual void update(Peripheral peripheral) = 0;
};

#endif /* PERIPHERALEVENTLISTENER_H_ */

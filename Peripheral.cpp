/*
 * Peripheral.cpp
 *
 *  Created on: 2009-09-29
 *      Author: oex
 */

#include "Peripheral.h"

#include "PeripheralEventListener.h"

#include <stdint.h>

Peripheral::Peripheral() {
	this->id = 0;
}

Peripheral::Peripheral(uint8_t id) {
	this->id = id;
}

Peripheral::~Peripheral() {

}

/**
 * @brief	Notify PeripheralEventListeners from an event.
 */
void Peripheral::notify() {
	// Browse through every listeners and tell them that
	// this object have an event pending
	for(int32_t i=0; i<listeners.size(); i++) {
		if(listeners.getElement(i) != 0) {
			listeners.getElement(i)->update(this);
		}
	}
}

/**
 * @brief	Add an EventListener to the list.
 */
void Peripheral::addEventListener(PeripheralEventListener *listener) {
	//listeners.push_back(listener);
	listeners.addElement(listener);
}

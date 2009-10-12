/*
 * Peripheral.cpp
 *
 *  Created on: 2009-09-29
 *      Author: oex
 */

#include "Peripheral.h"

#include "PeripheralEventListener.h"

#include <vector>
#include <stdint.h>

Peripheral::Peripheral() {
	// Empty the listener container
	listeners.clear();
}

Peripheral::~Peripheral() {

}

/**
 * @brief	Notify PeripheralEventListeners from an event.
 */
void Peripheral::notify() {
	// Browse through every listeners and tell them that
	// this object have an event pending
	for(uint32_t i=0; i<listeners.size(); i++) {
		if(listeners[i] != 0) {
			listeners[i]->update(this);
		}
	}
}

/**
 * @brief	Add an EventListener to the list.
 */
void Peripheral::addEventListener(PeripheralEventListener *listener) {
	listeners.push_back(listener);
}

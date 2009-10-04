/*
 * Peripheral.cpp
 *
 *  Created on: 2009-09-29
 *      Author: oex
 */

#include "Peripheral.h"

Peripheral::Peripheral() {
	// TODO Auto-generated constructor stub

}

Peripheral::~Peripheral() {
	// TODO Auto-generated destructor stub
}

/**
 * @brief	Default Peripheral interrupt handler.
 * @todo	Should do something smarter than while(1).
 */
void Peripheral::handleInterrupt() {
	while(1) {

	}
}

/**
 * @brief Notify PeripheralEventListeners from an event.
 */
void Peripheral::notify() {

}

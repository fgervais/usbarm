/*
 * Uart.cpp
 *
 *  Created on: 2009-09-29
 *      Author: oex
 */

#include "Uart.h"

Uart::Uart() {

}

Uart::~Uart() {

}

/**
 * @brief Handle the Uart interrupt (Send/Receive).
 */
void Uart::handleInterrupt() {
	/* Receive buffer full */

	// Get data
	notify();


	/* Send buffer empty */
}

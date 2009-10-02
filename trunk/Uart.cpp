/*
 * Uart.cpp
 *
 *  Created on: 2009-09-29
 *      Author: oex
 */

#include "Uart.h"

Uart::Uart() {
	// TODO Auto-generated constructor stub

}

Uart::~Uart() {
	// TODO Auto-generated destructor stub
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

/*
 * Uart.h
 *
 *  Created on: 2009-09-29
 *      Author: oex
 */

#ifndef UART_H_
#define UART_H_

#include "Peripheral.h"

class Uart: public Peripheral {
public:
	Uart();
	virtual ~Uart();

	void handleInterrupt();
};

#endif /* UART_H_ */

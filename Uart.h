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

	//                fck = 2 MHz
	//  baudrate =  ---------------
	//              (16 * USARTDIV)

	static const uint8_t UART_BAUDRATE_4800		= ;	/** Uart Speed 4800 baud/s */
	static const uint8_t UART_BAUDRATE_9600		= ;	/** Uart Speed 9600 baud/s */
	static const uint8_t UART_BAUDRATE_19200	= ;	/** Uart Speed 19200 baud/s */
	static const uint8_t UART_BAUDRATE_38400	= ;	/** Uart Speed 38400 baud/s */
	static const uint8_t UART_BAUDRATE_115200	= ;	/** Uart Speed 115200 baud/s */





	Uart();
	virtual ~Uart();

	void sendInterrupt();
	void receiveInterrupt();
};

#endif /* UART_H_ */

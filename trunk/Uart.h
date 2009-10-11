 /*
 * Uart.h
 *
 *  Created on: 2009-09-29
 *      Author: oex
 */

#ifndef UART_H_
#define UART_H_

#include "Peripheral.h"
#include "stm32f10x.h"

#include <iostream>
#include <queue>



class UartConfiguration;

class Uart: public Peripheral {
public:

	static const uint32_t UART_WORD_LENGTH_8BIT		= 0x00000000;	/** Uart Word Lenght of 8 bit */
	static const uint32_t UART_WORD_LENGTH_9BIT		= 0x00001000;	/** Uart Word Lenght of 9 bit  */

	static const uint32_t UART_1_STOPBIT			= 0x00000000;	/** Uart 1 Stop Bit */
	static const uint32_t UART_0p5_STOPBIT			= 0x00001000;	/** Uart 0.5 Stop Bit */
	static const uint32_t UART_2_STOPBIT			= 0x00002000;	/** Uart 2 Stop Bit */
	static const uint32_t UART_1p5_STOPBIT			= 0x00003000;	/** Uart 1.5 Stop Bit */

	static const uint32_t UART_PARITY_DISABLE 		= 0x00000000;	/** Disable Parity */
	static const uint32_t UART_PARITY_ENABLE 		= 0x00000400;	/** Enable Parity */

	static const uint32_t UART_PARITY_EVEN 			= 0x00000000;	/** Parity Even */
	static const uint32_t UART_PARITY_ODD 			= 0x00000200;	/** Parity Odd */

	static const uint32_t UART_DISABLE	 			= 0x00000000;	/** UART Disabled */
	static const uint32_t UART_ENABLE	 			= 0x00002000;	/** UART Enabled */

	static const uint32_t UART_TX_DISABLE	 		= 0x00000000;	/** UART Disabled */
	static const uint32_t UART_TX_ENABLE	 		= 0x00000008;	/** UART Enabled */

	static const uint32_t UART_RX_DISABLE	 		= 0x00000000;	/** UART Disabled */
	static const uint32_t UART_RX_ENABLE	 		= 0x00000004;	/** UART Enabled */

	static const uint32_t UART_TX_DATA_REGISTER		= 0x00000080; /** UART Transmission
																data register is empty */

private:
	USART_TypeDef *uartRegisters;
	uint32_t clockFrequency;
	uint16_t calculateBRR(uint16_t baudrate);
	std::queue<int8_t> charBuffer;

public:

	Uart(USART_TypeDef *uartRegisters, uint32_t PCLK1_Frequency);
	virtual ~Uart();

	void configure(UartConfiguration config);
	void write(char* data, uint16_t lenght);
	char read(uint8_t lenght);
	void sendInterrupt();
	void receiveInterrupt();


};

#endif /* UART_H_ */

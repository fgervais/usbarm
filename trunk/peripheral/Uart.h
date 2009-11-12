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
#include "Queue.h"

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

	static const uint32_t UART_TX_DISABLE	 		= 0x00000000;	/** UART Transmitter Disabled */
	static const uint32_t UART_TX_ENABLE	 		= 0x00000008;	/** UART Transmitter Enabled */

	static const uint32_t UART_RX_DISABLE	 		= 0x00000000;	/** UART Receiver Disabled */
	static const uint32_t UART_RX_ENABLE	 		= 0x00000004;	/** UART Receiver Enabled */

	static const uint32_t UART_TX_DATA_REGISTER		= 0x00000080;   /** UART Transmission
																        data register is empty */

	static const uint32_t UART_RX_DATA_REGISTER 	= 0x00000020; 	/** UART Receive data register
																					is not empty */

	static const uint32_t UART_TC_DATA_REGISTER		= 0x00000040;   /** UART Transmission
																        complete data register is empty */
	static const uint32_t UART_TC_DATA_REGISTER_CLR	= ~0x00000040;   /** Clear UART Transmission
																        data register is empty */

	static const uint32_t UART_TX_INTERRUPT_ENABLE   = 0x00000080;  /** UART Transmit Interrupt enable */
	static const uint32_t UART_TX_INTERRUPT_DISABLE  = ~0x00000080;  /** UART Transmit Interrupt disable*/

	static const uint32_t UART_TC_INTERRUPT_ENABLE   = 0x00000040;  /** UART Transmition complete Interrupt enable */
	static const uint32_t UART_TC_INTERRUPT_DISABLE  = ~0x00000040;  /** UART Transmition complete Interrupt disable*/

private:
	USART_TypeDef *uartRegisters;
	Queue<char>* txQueue;
	//Queue<char>* rxQueue;
	uint32_t clockFrequency;
	uint16_t calculateBRR(uint16_t baudrate);

public:

	Uart(USART_TypeDef *uartRegisters, uint8_t id,
			uint32_t PCLK1_Frequency);
	virtual ~Uart();
	void configure(UartConfiguration config);
	void write(char* data, uint16_t length);
	char read();
	void poll();
	void sendInterrupt();
	void receiveInterrupt();


};

#endif /* UART_H_ */

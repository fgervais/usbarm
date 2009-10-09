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

class UartConfiguration;

class Uart: public Peripheral {
public:

	/**              fck = 72000000
	    baudrate =  ----------------
	                 (16 * USARTDIV)
	*/

	/*	USARTDIV = 937.5, Fraction = 16 * 0.5 = 8 = 0x8,
		Mantisse = 937 = 0x3A9, BRR = 0x00003A9C  */
	static const uint32_t UART_BAUDRATE_4800		= 0x00003A9C;	/** Uart Speed 4800 baud/s */

	/* USARTDIV = 468.75,  Fraction = 16 * 0.75 = 12 = 0xC,
	   Mantisse = 468 = 0x1D4, BRR = 0x000001D4C  */
	static const uint32_t UART_BAUDRATE_9600		= 0x000001D4C;	/** Uart Speed 9600 baud/s */

	/* USARTDIV = 234.375, Fraction = 16 * 0.75 = 12 = 0xC,
	   Mantisse = 234 = 0xEA, BRR = 0x00000EAC */
	static const uint32_t UART_BAUDRATE_19200		= 0x00000EAC;	/** Uart Speed 19200 baud/s */

	/* USARTDIV = 117.188, Fraction = 16 * 0.188 = 3 = 0x3,
	 * Mantisse = 117 = 0x75, BRR = 0x00000753  */
	static const uint32_t UART_BAUDRATE_38400		= 0x00000753;	/** Uart Speed 38400 baud/s */

	/* USARTDIV = 39.0625, Fraction = 16 * 0.0625 = 1 = 0x1,
	   Mantisse = 39 = 0x3, BRR = 0x00000271  */
	static const uint32_t UART_BAUDRATE_115200		= 0x00000271;	/** Uart Speed 115200 baud/s */

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

private:
	USART_TypeDef *uartRegisters;

public:
	Uart(USART_TypeDef *uartRegisters);
	virtual ~Uart();

	void configure(UartConfiguration config);
	void write(char data, uint8_t lenght);
	char read(uint8_t lenght);
	void sendInterrupt();
	void receiveInterrupt();


};

#endif /* UART_H_ */

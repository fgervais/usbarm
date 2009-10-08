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

	/**              fck = 7200000
	    baudrate =  ---------------
	                (16 * USARTDIV)
	*/

	/*	USARTDIV = 93.75, Fraction = 16 * 0.75 = 12 = 0xC,
		Mantisse = 93 = 0x5D, BRR = 0x000005DC  */
	static const uint32_t UART_BAUDRATE_4800		= 0x000005DC;	/** Uart Speed 4800 baud/s */

	/* USARTDIV = 46.875,  Fraction = 16 * 0.875 = 14 = 0xE,
	   Mantisse = 46 = 0x2E, BRR = 0x000002EE  */
	static const uint32_t UART_BAUDRATE_9600		= 0x000002EE;	/** Uart Speed 9600 baud/s */

	/* USARTDIV = 23.4375, Fraction = 16 * 0.4375 = 7 = 0x7,
	   Mantisse = 23 = 0x17, BRR = 0x00000177 */
	static const uint32_t UART_BAUDRATE_19200	= 0x00000177;	/** Uart Speed 19200 baud/s */

	/* USARTDIV = 11.7188, Fraction = 16 * 0.7188 = ceil(11.5008) = 12 = 0xC,
	 * Mantisse = 11 = 0xB, BRR = 0x000000BC  */
	static const uint32_t UART_BAUDRATE_38400	= 0x000000BC;	/** Uart Speed 38400 baud/s */

	/* USARTDIV = 3.90625, Fraction = 16 * 0.90625 = ceil(14.5) = 15 = 0xF,
	   Mantisse = 3 = 0x3, BRR = 0x0000003F  */
	static const uint8_t UART_BAUDRATE_115200	= 0x0000003F;	/** Uart Speed 115200 baud/s */

	static const uint8_t UART_WORD_LENGTH_8BIT	= 0;	/** Uart Word Lenght of 8 bit */
	static const uint8_t UART_WORD_LENGTH_9BIT	= 1;	/** Uart Word Lenght of 9 bit  */

	static const uint8_t UART_1_STOPBIT			= 0;	/** Uart 1 Stop Bit */
	static const uint8_t UART_0p5_STOPBIT		= 1;	/** Uart 0.5 Stop Bit */
	static const uint8_t UART_2_STOPBIT			= 2;	/** Uart 2 Stop Bit */
	static const uint8_t UART_1p5_STOPBIT		= 3;	/** Uart 1.5 Stop Bit */

	static const uint8_t UART_PARITY_DISABLE 	= 0;	/** Disable Parity */
	static const uint8_t UART_PARITY_ENABLE 	= 1;	/** Enable Parity */

	static const uint8_t UART_PARITY_EVEN 		= 0;	/** Parity Even */
	static const uint8_t UART_PARITY_ODD 		= 1;	/** Parity Odd */

private:
	USART_TypeDef *uartRegisters;

public:
	Uart(USART_TypeDef *uartRegisters);
	virtual ~Uart();

	void configure(UartConfiguration config);
	void sendInterrupt();
	void receiveInterrupt();


};

#endif /* UART_H_ */

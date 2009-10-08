/*
 * UartConfig.h
 *
 *  Created on: 2009-10-06
 *      Author: oex
 */

#ifndef UARTCONFIG_H_
#define UARTCONFIG_H_

class UartConfig {
public:
	UartConfig();
	virtual ~UartConfig();

	uint8_t baudrate;
	uint8_t parity;
	uint8_t stopBit;
	uint8_t wordLenght;
};

#endif /* UARTCONFIG_H_ */

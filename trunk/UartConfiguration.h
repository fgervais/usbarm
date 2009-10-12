/*
 * UartConfig.h
 *
 *  Created on: 2009-10-06
 *      Author: oex
 */

#ifndef UARTCONFIGURATION_H_
#define UARTCONFIGURATION_H_

#include "stm32f10x.h"

class UartConfiguration {
public:
	UartConfiguration();
	virtual ~UartConfiguration();

	uint8_t baudrate;
	uint8_t parity;
	uint8_t stopBit;
	uint8_t wordLenght;
};

#endif /* UARTCONFIGURATION_H_ */

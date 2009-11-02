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

	uint16_t baudrate;
	uint32_t parityType;
	uint32_t parityEnable;
	uint32_t stopBit;
	uint32_t wordLenght;
};

#endif /* UARTCONFIGURATION_H_ */

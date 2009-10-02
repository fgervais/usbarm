/*
 * Application.cpp
 *
 *  Created on: 2009-09-29
 *      Author: oex
 */

#include "Microcontroller.h"

#include "STM32F103.h"
#include "Uart.h"

int main(void) {

	Uart *uart1 = STM32F103::getUart1();
	STM32F103::getUart1()->handleInterrupt();

}

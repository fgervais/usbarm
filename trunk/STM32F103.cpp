/*
 * STM32F103.cpp
 *
 *  Created on: Oct 1, 2009
 *      Author: fgervais
 */

#include "STM32F103.h"

#include "Uart.h"
#include "Gpio.h"

#include "stm32f10x.h"

STM32F103::STM32F103() {
	// TODO Auto-generated constructor stub

}

STM32F103::~STM32F103() {
	// TODO Auto-generated destructor stub
}

/**
 * @brief	This function return an instance to the actual Uart1.
 * @return	The STM32F103 Uart1
 */
Uart* STM32F103::getUart1() {
	if(uart1 == 0) {
		uart1 = new Uart();
		// Uart should somehow be initialized here
	}
	return uart1;
}

Gpio* STM32F103::getGpioA() {
	if(gpioA == 0) {
		gpioA = new Gpio(GPIOA);
		// Gpio should somehow be initialized here
	}
	return gpioA;
}

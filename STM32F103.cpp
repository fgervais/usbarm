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

/* Static init. Required to make the compiler happy */
Uart* STM32F103::uart1 = 0;
Gpio* STM32F103::gpioA = 0;

STM32F103::STM32F103() {


}

STM32F103::~STM32F103() {

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
		// Send clock to GPIO A
		RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	}
	return gpioA;
}

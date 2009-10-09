/*
 * Application.cpp
 *
 *  Created on: 2009-09-29
 *      Author: oex
 */

#include "STM32F103.h"
#include "GpioConfiguration.h"
#include "GpioPinConfiguration.h"
#include "GpioPin.h"
#include "Gpio.h"
#include "Uart.h"
#include "UartConfiguration.h"

#include <stdint.h>

int main(void) {
	// Setup STM32 system (clock, PLL and Flash configuration)
	SystemInit();

	Uart *uart1 = STM32F103::getUart1();

	UartConfiguration uart1Config;
	uart1Config.baudrate 		= Uart::UART_BAUDRATE_9600;
	uart1Config.stopBit 		= Uart::UART_1_STOPBIT;
	uart1Config.parityEnable 	= Uart::UART_PARITY_DISABLE;
	uart1Config.wordLenght		= Uart::UART_1_STOPBIT;
	uart1->configure(uart1Config);

	Gpio *gpioA = STM32F103::getGpioA();

	// Create a new GpioConfiguration with FLOATING_INPUT as default for all pins
	//GpioConfiguration portConfig(Gpio::FLOATING_INPUT);
	GpioConfiguration portConfig(Gpio::AF_PUSH_PULL_OUTPUT | Gpio::OUTPUT_SPEED_50MHZ);


	gpioA->configure(portConfig);

	GpioPinConfiguration pinConfig;
	pinConfig.pin = Gpio::GP_PUSH_PULL_OUTPUT | Gpio::OUTPUT_SPEED_50MHZ;
	gpioA->getPin(0)->configure(pinConfig);

	GpioPin *led = gpioA->getPin(0);

	// Blink led
	while(1) {
		led->setHigh();	// On
		for(uint32_t i=0; i<1000000; i++);
		uart1->write('a',1);

		led->setLow();	// Off
		for(uint32_t i=0; i<1000000; i++);
		uart1->write('a',1);
	}
}

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
#include "Usb.h"

#include <stdint.h>

void main_francois();
void main_remi();

int main(void) {
	main_francois();
	//main_remi();
}

void main_francois() {
	// Setup STM32 system (clock, PLL and Flash configuration)
	SystemInit();

	Gpio *gpioA = STM32F103::getGpioA();

	// Set default port behavior
	GpioConfiguration portConfig(Gpio::FLOATING_INPUT);
	gpioA->configure(portConfig);

	// Configure blinking led
	GpioPinConfiguration ledPinConfig;
	ledPinConfig.pin = Gpio::GP_PUSH_PULL_OUTPUT | Gpio::OUTPUT_SPEED_50MHZ;
	gpioA->getPin(0)->configure(ledPinConfig);

	GpioPin *led = gpioA->getPin(0);

	// Create the usb port
	STM32F103::getUsb();

	// Clear interrupt pending bit
	EXTI->PR |= 0x01;

	// Reset led sequence
	for(uint32_t j=0; j<10; j++) {
		led->setHigh();	// On
		for(uint32_t i=0; i<100000; i++);
		led->setLow();	// Off
		for(uint32_t i=0; i<100000; i++);
	}

	// Blink led
	while(1) {
		led->setHigh();	// On
		for(uint32_t i=0; i<1000000; i++);

		led->setLow();	// Off
		for(uint32_t i=0; i<1000000; i++);

		// Simulate an external interrupt
		EXTI->SWIER |= 0x02;
	}
}

void main_remi() {
	char buf[8];
	buf[0] = 't';
	buf[1] = 'e';
	buf[2] = 's';
	buf[3] = 't';
	buf[4] = 't';
	buf[5] = 't';
	buf[6] = ' ';
	buf[7] = 0;
	//buf[8] = 0;
	//buf[9] = 0;
	/*buf[6] = 'e';
	buf[7] = 's';
	buf[8] = 't';
	buf[9] = ' ';
	buf[10] = 0;*/

	// Setup STM32 system (clock, PLL and Flash configuration)
	SystemInit();

	Uart *uart1 = STM32F103::getUart1();

	UartConfiguration uart1Config;
	uart1Config.baudrate 		= 9600;
	uart1Config.stopBit 		= Uart::UART_1_STOPBIT;
	uart1Config.parityEnable 	= Uart::UART_PARITY_DISABLE;
	uart1Config.wordLenght		= Uart::UART_1_STOPBIT;
	uart1->configure(uart1Config);

	Gpio *gpioA = STM32F103::getGpioA();

	// Set default port behavior
	GpioConfiguration portConfig(Gpio::AF_PUSH_PULL_OUTPUT | Gpio::OUTPUT_SPEED_50MHZ);
	gpioA->configure(portConfig);

	// Configure blinking led
	GpioPinConfiguration ledPinConfig;
	ledPinConfig.pin = Gpio::GP_PUSH_PULL_OUTPUT | Gpio::OUTPUT_SPEED_50MHZ;
	gpioA->getPin(0)->configure(ledPinConfig);

	GpioPin *led = gpioA->getPin(0);

	// Blink led
	while(1) {
		led->setHigh();	// On
		for(uint32_t i=0; i<1000000; i++);

		uart1->write(buf,sizeof(buf));

		led->setLow();	// Off
		for(uint32_t i=0; i<1000000; i++);
		//uart1->write('d',1);
	}
}

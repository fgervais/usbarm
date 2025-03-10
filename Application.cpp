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
#include "NesControllerInterface.h"

#include <stdint.h>

void main_francois();
void main_remi();
void blinky();

int main(void) {
	main_francois();
	//main_remi();
	//blinky();
}

void main_francois() {
	// Setup STM32 system (clock, PLL and Flash configuration)
	SystemInit();

	Gpio *gpioA = STM32F103::getGpioA();
	Gpio *gpioB = STM32F103::getGpioB();
	Gpio *gpioC = STM32F103::getGpioC();

	// Set default port behavior
	GpioConfiguration portConfig(Gpio::FLOATING_INPUT);
	gpioA->configure(portConfig);

	// Configure blinking led
	GpioPinConfiguration ledPinConfig;
	ledPinConfig.pin = Gpio::GP_PUSH_PULL_OUTPUT | Gpio::OUTPUT_SPEED_50MHZ;
	gpioA->getPin(0)->configure(ledPinConfig);

	GpioPin *led = gpioA->getPin(0);

	// Create the usb port
	Usb* usb = STM32F103::getUsb();

	// Create a new NES controller interface
	AFIO->MAPR |= AFIO_MAPR_SWJ_CFG_DISABLE;	// JTAG remap
	NesControllerInterface* nesInterface = new NesControllerInterface(gpioB->getPin(3), gpioB->getPin(4), gpioC->getPin(5));
	usb->addEventListener(nesInterface);

	usb->listenForDevice();

	while(!usb->deviceDetected());

	//debug
	// Blink led fast
	led->setHigh();	// On
	for(uint32_t i=0; i<100000; i++);
	led->setLow();	// Off
	for(uint32_t i=0; i<100000; i++);

	usb->enumerateDevice();

	// Blink led
	while(1) {

		//if(usb->deviceDetected()) {
			/*led->setHigh();	// On
			for(uint32_t i=0; i<100000; i++);
			led->setLow();	// Off
			for(uint32_t i=0; i<100000; i++);*/

			//if(!usb->deviceEnumerated()) {

				//debug
				// Blink led fast
				/*GPIOA->BSRR |= 0x01;	// On
				for(uint32_t i=0; i<100000; i++);
				GPIOA->BRR |= 0x01;	// Off
				for(uint32_t i=0; i<100000; i++);

				usb->enumerateDevice();*/
			//}
			//else {
				usb->serviceHid();
			//}
		//}

		/*
		led->setHigh();	// On
		for(uint32_t i=0; i<1000000; i++);

		led->setLow();	// Off
		for(uint32_t i=0; i<1000000; i++);
		*/

		// Simulate an external interrupt
		//EXTI->SWIER |= EXTI_SWIER_SWIER1;
	}
}

void main_remi() {
	char buf[27] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm' ,'n', 'o', 'p' ,'q'
	,'r', 's','t','u','v','w','x','y','z',' '};
	// Setup STM32 system (clock, PLL and Flash configuration)
	SystemInit();





	Gpio *gpioA = STM32F103::getGpioA();
	// Set default port behavior
	GpioConfiguration portConfig(Gpio::AF_PUSH_PULL_OUTPUT | Gpio::OUTPUT_SPEED_50MHZ);
	gpioA->configure(portConfig);

	Uart *uart1 = STM32F103::getUart1();
	UartConfiguration uart1Config;
	uart1Config.baudrate 		= 9600;
	uart1Config.stopBit 		= Uart::UART_1_STOPBIT;
	uart1Config.parityEnable 	= Uart::UART_PARITY_DISABLE;
	uart1Config.wordLenght		= Uart::UART_WORD_LENGTH_8BIT;
	uart1->configure(uart1Config);

	//Uart *uart2 = STM32F103::getUart2();
	// Uart2 config

	// Tag each Uart with their respective source
	uart1->setTag(Peripheral::Controller);
	//uart2->setTag(Peripheral::Drive);

	// Configure blinking led
	GpioPinConfiguration ledPinConfig;
	ledPinConfig.pin = Gpio::GP_PUSH_PULL_OUTPUT | Gpio::OUTPUT_SPEED_50MHZ;
	gpioA->getPin(0)->configure(ledPinConfig);

	GpioPin *led = gpioA->getPin(0);

	// Blink led
	while(1) {
		led->setHigh();	// On
		for(uint32_t i=0; i<1000000; i++){
			uart1->poll();
		}

		uart1->write((char *)buf, 27);

		led->setLow();	// Off
		for(uint32_t i=0; i<1000000; i++){
			uart1->poll();
		}
	}
}

void blinky() {
	// Setup STM32 system (clock, PLL and Flash configuration)
	SystemInit();

	Gpio *gpioA = STM32F103::getGpioA();

	// Configure blinking led
	GpioPinConfiguration ledPinConfig;
	ledPinConfig.pin = Gpio::GP_PUSH_PULL_OUTPUT | Gpio::OUTPUT_SPEED_50MHZ;
	gpioA->getPin(0)->configure(ledPinConfig);

	GpioPin *led = gpioA->getPin(0);

	while(1) {
		led->setHigh();	// On
		for(uint32_t i=0; i<1000000; i++);
		led->setLow();	// Off
		for(uint32_t i=0; i<1000000; i++);
	}
}

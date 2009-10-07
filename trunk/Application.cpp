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

#include <stdint.h>

int main(void) {
	// Setup STM32 system (clock, PLL and Flash configuration)
	SystemInit();

	Uart *uart1 = STM32F103::getUart1();

	Gpio *gpioA = STM32F103::getGpioA();

	// Create a new GpioConfiguration with FLOATING_INPUT as default for all pins
	GpioConfiguration portConfig(Gpio::FLOATING_INPUT);
	gpioA->configure(portConfig);

	GpioPinConfiguration pinConfig;
	pinConfig.pin = Gpio::GP_PUSH_PULL_OUTPUT | Gpio::OUTPUT_SPEED_50MHZ;
	gpioA->getPin(0)->configure(pinConfig);

	GpioPin *led = gpioA->getPin(0);

	// Blink led
	while(1) {
		led->setHigh();	// On
		for(uint32_t i=0; i<1000000; i++);
		led->setLow();	// Off
		for(uint32_t i=0; i<1000000; i++);
	}

}

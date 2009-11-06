/*
 * Gpio.h
 *
 *  Created on: 2009-09-29
 *      Author: oex
 */

#ifndef GPIO_H_
#define GPIO_H_

#include "Peripheral.h"

#include "stm32f10x.h"

class GpioConfiguration;
class GpioPin;

/**
 * General purpose IO port.
 */
class Gpio: public Peripheral {
public:
	static const uint8_t OUTPUT_SPEED_10MHZ		= 0x01;	/** Output mode, max speed 10 MHz. */
	static const uint8_t OUTPUT_SPEED_2MHZ		= 0x02;	/** Output mode, max speed 2 MHz. */
	static const uint8_t OUTPUT_SPEED_50MHZ		= 0x03;	/** Output mode, max speed 50 MHz. */

	static const uint8_t ANALOG_INPUT			= 0x00;	/** Analog input mode */
	static const uint8_t FLOATING_INPUT			= 0x04; /** Floating input (reset state) */
	static const uint8_t PULLUP_PULLDOWN_INPUT 	= 0x08;	/** Input with pull-up / pull-down */

	static const uint8_t GP_PUSH_PULL_OUTPUT	= 0x00;	/** General purpose output push-pull */
	static const uint8_t GP_OPEN_DRAIN_OUTPUT	= 0x04; /** General purpose output Open-drain */
	static const uint8_t AF_PUSH_PULL_OUTPUT	= 0x08; /** Alternate function output Push-pull */
	static const uint8_t AF_OPEN_DRAIN_OUTPUT	= 0x0C;	/** Alternate function output Open-drain */

	Gpio(GPIO_TypeDef *gpioRegisters, uint8_t id);
	virtual ~Gpio();

	void configure(GpioConfiguration config);

	GpioPin* getPin(uint8_t number);

	uint32_t getData();
	void setData(uint32_t);

private:
	GPIO_TypeDef *gpioRegisters;
	GpioPin *gpioPins[16];
};

#endif /* GPIO_H_ */

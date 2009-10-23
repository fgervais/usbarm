/*
 * GpioPin.cpp
 *
 *  Created on: Oct 2, 2009
 *      Author: fgervais
 */

#include "GpioPin.h"
#include "GpioPinConfiguration.h"
#include "GpioPinEventListener.h"
#include "Gpio.h"

GpioPin::GpioPin(GPIO_TypeDef *gpioRegisters, uint8_t pinNumber, uint8_t portNumber) {
	this->gpioRegisters = gpioRegisters;
	this->pinNumber = pinNumber;
	this->portNumber = portNumber;

	// Initialization
	extiConfigured = 0;
}

GpioPin::~GpioPin() {

}

void GpioPin::extInterrupt() {
	// Browse through every listeners and tell them that
	// this object have an event pending
	for(int32_t i=0; i<listeners.size(); i++) {
		if(listeners.getElement(i) != 0) {
			listeners.getElement(i)->stateChanged(this);
		}
	}
}

/**
 * @brief	Configure this pin (Direction, Speed..).
 * @param config Configuration if the pin.
 */
void GpioPin::configure(GpioPinConfiguration config) {
	uint32_t configRegister;

	// Use port configuration low
	if(pinNumber < 8) {
		configRegister = gpioRegisters->CRL;
		// Clear the pin configuration
		configRegister &= ~(0x0F << (pinNumber*4));
		configRegister |= config.pin << (pinNumber*4);
		// Apply changes
		gpioRegisters->CRL = configRegister;
	}
	// Use port configuration high
	else {
		configRegister = gpioRegisters->CRH;
		// Clear the pin configuration
		configRegister &= ~(0x0F << ((pinNumber%8)*4));
		configRegister |= config.pin << ((pinNumber%8)*4);
		// Apply changes
		gpioRegisters->CRH = configRegister;
	}
}

/**
 * @brief	Check if the pin is at the high level.
 * @return	0 if false, true otherwise.
 */
uint32_t GpioPin::isHigh() {
	return gpioRegisters->IDR & (1 << pinNumber);
}

/**
 * @brief	Set the pin to the high level.
 */
void GpioPin::setHigh() {
	gpioRegisters->BSRR |= (1 << pinNumber);
}

/**
 * @brief	Set the pin to the low level.
 */
void GpioPin::setLow() {
	gpioRegisters->BRR |= (1 << pinNumber);
}

void GpioPin::addEventListener(GpioPinEventListener *listener) {
	if(!extiConfigured) {
		configureInterrupt();
		extiConfigured = 1;
	}
	listeners.addElement(listener);
}


void GpioPin::configureInterrupt() {
	/* Configure exti interrupt with ninja bit operations */
	// Clear current configuration
	AFIO->EXTICR[pinNumber >> 2] &= (0x00FF << (pinNumber & 0x0003));
	// Configure which port gets the external interrupt
	AFIO->EXTICR[pinNumber >> 2] |= ((portNumber-1) << (pinNumber & 0x0003));
	// Clear the interrupt mask
	EXTI->IMR |= (1<<pinNumber);
	// Clear the event mask
	EXTI->EMR |= (1<<pinNumber);
	// Set interrupt on rising edge
	EXTI->RTSR |= (1<<pinNumber);

	// Get the IRQn according to the pin number
	// Better way to do this anyone?
	uint8_t irqNumber;
	switch(pinNumber) {
	case 0:
		irqNumber = EXTI0_IRQn;
		break;
	case 1:
		irqNumber = EXTI1_IRQn;
		break;
	case 2:
		irqNumber = EXTI2_IRQn;
		break;
	case 3:
		irqNumber = EXTI3_IRQn;
		break;
	case 4:
		irqNumber = EXTI4_IRQn;
		break;
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		irqNumber = EXTI9_5_IRQn;
		break;
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
		irqNumber = EXTI15_10_IRQn;
		break;
	}

	/*
	 * Configure NVIC for GPIO interrupt
	 *
	 * Alright, lets try to explain all that.
	 *
	 * The number of priority bit can be anything from 1 to 8 bits
	 * depending on the Cortex-m3 implementation. This is why we rely
	 * on __NVIC_PRIO_BITS which has been defined by ST.
	 *
	 * IP[] array is 240 8bits registers for all 240 possible interrupts
	 * of the Cortex-m3. Only a small number of these are implemented by
	 * ST in the low-cost STM32. The interrupt number is defined as
	 * XXX_URQn by ST. This is what we use as the array index.
	 *
	 * This array contains the interrupt priority and sub priority and
	 * is *MSB FIRST*. This means that priority 1 is 0x80.
	 *
	 * ISER[] is an array of register use to enable the interrupt. There
	 * is 8 register of 32 bits. Since one bit is used to enable an
	 * interrupt, this gives use 256 possible interrupt which is enough
	 * for our 240 possible interrupt.
	 *
	 * To understand how we set that you have to see the XXX_IRQn value
	 * as two informations encoded in the same word. The first 5 bits
	 * is the interrupt number and the other upper bits are the
	 * number of the register in which the interrupt is located.
	 * This is why we shift right 5 bits and we mask XXX_IRQn with a
	 * 5 bits mask.
	 */
	uint8_t priority = 0;
	// Priority is on __NVIC_PRIO_BITS bits
	uint8_t priotityMask = (1 << __NVIC_PRIO_BITS) - 1;
	// Priority is shifted because it's MSB first
	NVIC->IP[irqNumber] = (priority & priotityMask) << __NVIC_PRIO_BITS;
	// Clear interrupt pending bit
	EXTI->PR |= 0x01;
	NVIC->ICPR[irqNumber >> 5] = 1 << (irqNumber & 0x1F);
	// Enable the interrupt
	NVIC->ISER[irqNumber >> 5] = 1 << (irqNumber & 0x1F);
}

/*
 * Timer.cpp
 *
 *  Created on: 2009-09-29
 *      Author: oex
 */

#include "Timer.h"
#include "TimerConfiguration.h"
#include "TimerOverflowListener.h"

Timer::Timer(TIM_TypeDef* timerRegisters, uint8_t id) : Peripheral(id) {
	this->timerRegisters = timerRegisters;

	// Initialization
	mode = None;
	overflowiConfigured = 0;
}

Timer::~Timer() {

}

/**
 * @brief Function called by the overflow interrupt.
 */
void Timer::overflowInterrupt() {
	// Browse through every listeners and tell them that
	// this object have an event pending
	for(int32_t i=0; i<overflowListeners.size(); i++) {
		if(overflowListeners.getElement(i) != 0) {
			overflowListeners.getElement(i)->timerOverflowed(this);
		}
	}
}

/**
 * @brief Configure the timer in a certain mode.
 *
 * The timer needs to be in the right mode before adding
 * an event listener.
 *
 * @param config Configuration structure
 */
void Timer::configure(TimerConfiguration config) {
	switch(config.mode) {
	case Timer::COUNTER_MODE:
		timerRegisters->PSC = config.prescaler;
		timerRegisters->ARR = config.autoReload;
		counterMode();
		break;
	case Timer::PWM_INPUT_MODE:
		break;
	}
}

/**
 * Add a timer overflow listener.
 * @param listener Overflow listener.
 * @return 0 if successful, 1 if the timer is not in the right mode.
 */
uint8_t Timer::addEventListener(TimerOverflowListener* listener) {
	// Timer should be configured in the right mode first
	if(mode == Counter) {
		if(!overflowiConfigured) {
			configureOverflowInterrupt();
			overflowiConfigured = 1;
		}
		overflowListeners.addElement(listener);
		return 0;
	}
	return 1;
}

/**
 * @brief Enable the timer.
 */
void Timer::enable() {
	timerRegisters->CR1 |= TIM_CR1_CEN;
}

/**
 * @brief Disable the timer.
 */
void Timer::disable() {
	timerRegisters->CR1 &= ~TIM_CR1_CEN;
}

/**
 * @brief Set the timer in counter mode.
 */
void Timer::counterMode() {
	/*
	 * No clock division
	 * Auto reload buffered
	 * Edge aligned mode
	 * Up counter
	 * One pulse mode disabled
	 * Only counter overflow/underflow generates an update interrupt
	 * Update event enabled
	 * *Counter disabled* (Must be enabled manually by user)
	 */
	timerRegisters->CR1 = TIM_CR1_ARPE | TIM_CR1_URS;

	mode = Counter;
}

/**
 * @brief Configure the overflow interrupt.
 */
void Timer::configureOverflowInterrupt() {
	// Get the IRQn according to the timer id
	// Better way to do this anyone?
	uint8_t irqNumber;
	switch(getId()) {
	case 1:
		// Timer 1 is an advanced control timer and is not supported
		break;
	case 2:
		irqNumber = TIM2_IRQn;
		break;
	case 3:
		irqNumber = TIM3_IRQn;
		break;
	case 4:
		irqNumber = TIM4_IRQn;
		break;
	case 5:
		irqNumber = TIM5_IRQn;
		break;
	case 6:
	case 7:
		// Timer 6 and 7 are basic timers and are not supported
		break;
	case 8:
		// Timer 8 is an advanced control timer and is not supported
		break;
	}

	/* Note: there is an explanation of the NVIC setting in GpioPin.cpp */

	uint8_t priority = 0;
	// Priority is on __NVIC_PRIO_BITS bits
	uint8_t priotityMask = (1 << __NVIC_PRIO_BITS) - 1;
	// Priority is shifted because it's MSB first
	NVIC->IP[irqNumber] = (priority & priotityMask) << __NVIC_PRIO_BITS;
	// Clear update interrupt flag bit
	timerRegisters->SR &= ~TIM_SR_UIF;
	NVIC->ICPR[irqNumber >> 5] = 1 << (irqNumber & 0x1F);
	// Enable the interrupt
	NVIC->ISER[irqNumber >> 5] = 1 << (irqNumber & 0x1F);
	timerRegisters->DIER |= TIM_DIER_UIE;
}

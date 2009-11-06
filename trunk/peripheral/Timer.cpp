/*
 * Timer.cpp
 *
 *  Created on: 2009-09-29
 *      Author: oex
 */

#include "Timer.h"
#include "TimerConfiguration.h"

Timer::Timer(TIM_TypeDef* timerRegisters, uint8_t id) : Peripheral(id) {

}

Timer::~Timer() {

}

void Timer::configure(TimerConfiguration config) {
	switch(config.mode) {
	case Timer::COUNTER_MODE:
		break;
	case Timer::PWM_INPUT_MODE:
		break;
	}
}

void Timer::enable() {
	timerRegisters->CR1 |= TIM_CR1_CEN;
}

void Timer::disable() {
	timerRegisters->CR1 &= ~TIM_CR1_CEN;
}

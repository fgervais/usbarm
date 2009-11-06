/*
 * Timer.h
 *
 *  Created on: 2009-09-29
 *      Author: oex
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "Peripheral.h"

#include "stm32f10x.h"

class TimerConfiguration;

class Timer: public Peripheral {
public:
	// These values are use to select the mode and have
	// nothing to do with register value
	static const uint16_t COUNTER_MODE		= 0x0000;
	static const uint16_t PWM_INPUT_MODE	= 0x0001;


	Timer(TIM_TypeDef* timerRegisters, uint8_t id);
	virtual ~Timer();

	void configure(TimerConfiguration config);
	void enable();
	void disable();
private:
	TIM_TypeDef* timerRegisters;
};

#endif /* TIMER_H_ */

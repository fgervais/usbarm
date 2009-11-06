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
class TimerOverflowListener;

class Timer: public Peripheral {
public:
	// These values are use to select the mode and have
	// nothing to do with register value
	static const uint16_t COUNTER_MODE		= 0x0001;
	static const uint16_t PWM_INPUT_MODE	= 0x0002;

	enum Mode { None =0, Counter, PwmInput };

	Timer(TIM_TypeDef* timerRegisters, uint8_t id);
	virtual ~Timer();

	void overflowInterrupt();
	void configure(TimerConfiguration config);
	uint8_t addEventListener(TimerOverflowListener* listener);
	void enable();
	void disable();
private:
	TIM_TypeDef* timerRegisters;
	Mode mode;
	Vector<TimerOverflowListener*> overflowListeners;
	uint8_t overflowiConfigured;

	void counterMode();
	void configureOverflowInterrupt();
};

#endif /* TIMER_H_ */

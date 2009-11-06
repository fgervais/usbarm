/*
 * TimerEventListener.h
 *
 *  Created on: Nov 6, 2009
 *      Author: fgervais
 */

#ifndef TIMEREVENTLISTENER_H_
#define TIMEREVENTLISTENER_H_

class Timer;

class TimerEventListener {
public:
	TimerEventListener();
	virtual ~TimerEventListener();

	virtual void timerOverflowed(Timer* timer) = 0;
};

#endif /* TIMEREVENTLISTENER_H_ */

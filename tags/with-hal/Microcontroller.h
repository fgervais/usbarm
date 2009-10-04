/*
 * Microcontroller.h
 *
 *  Created on: 2009-09-29
 *      Author: oex
 */

#ifndef MICROCONTROLLER_H_
#define MICROCONTROLLER_H_

class Uart;
class Gpio;

class Microcontroller {
public:
	Microcontroller();
	virtual ~Microcontroller();

	// TODO: Need way better handling here such as exceptions.
	virtual Uart* getUart1() { return 0; }
	virtual Gpio* getGpioA() { return 0; }
};

#endif /* MICROCONTROLLER_H_ */

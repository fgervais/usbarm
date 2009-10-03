/*
 * STM32F103.h
 *
 *  Created on: Oct 1, 2009
 *      Author: fgervais
 */

#ifndef STM32F103_H_
#define STM32F103_H_

#include "Microcontroller.h"

class Uart;
class Gpio;

class STM32F103: public Microcontroller {
public:
	static Uart* getUart1();
	static void ioctl(Gpio* port);

private:
	// This ensure no instance of this class
	STM32F103();
	virtual ~STM32F103();
	STM32F103(const STM32F103&);
	STM32F103& operator= (const STM32F103&);

	static Uart *uart1;
};

#endif /* STM32F103_H_ */

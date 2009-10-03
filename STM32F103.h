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
	STM32F103();
	virtual ~STM32F103();

	virtual Uart* getUart1();
	virtual Gpio* getGpioA();

private:

	Uart *uart1;
	Gpio *gpioA;
};

#endif /* STM32F103_H_ */

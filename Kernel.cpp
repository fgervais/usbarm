/*
 * Kernel.cpp
 *
 *  Created on: Oct 3, 2009
 *      Author: fgervais
 */

#include "Kernel.h"

#include "STM32F103.h"
#include "Microcontroller.h"
#include "Gpio.h"

/* Static init. Required to make the compiler happy */
Microcontroller* Kernel::mcu = 0;

Kernel::Kernel() {
	// TODO Auto-generated constructor stub

}

Kernel::~Kernel() {
	// TODO Auto-generated destructor stub
}

Microcontroller* Kernel::getMicrocontroller() {
	if(mcu == 0) {
		mcu = new STM32F103();
	}
	return mcu;
}

void Kernel::ioctl(Gpio* port) {

}

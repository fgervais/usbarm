/*
 * Kernel.h
 *
 *  Created on: Oct 3, 2009
 *      Author: fgervais
 */

#ifndef KERNEL_H_
#define KERNEL_H_

class Microcontroller;
class Gpio;

class Kernel {
public:
	Kernel();
	virtual ~Kernel();

	static Microcontroller* getMicrocontroller();
	static void ioctl(Gpio* port);

private:
	static Microcontroller* mcu;
};

#endif /* KERNEL_H_ */

/*
 * MAX3421E.h
 *
 *  Created on: Oct 13, 2009
 *      Author: fgervais
 */

#ifndef MAX3421E_H_
#define MAX3421E_H_

#include <stdint.h>

class Spi;

class MAX3421E {
public:
	MAX3421E(Spi *spi);
	virtual ~MAX3421E();

	// MAX3421E Registers
	static const uint8_t RCVFIFO	= 1;
	static const uint8_t SNDFIFO	= 2;
	static const uint8_t SUDFIFO	= 3;
	static const uint8_t RCVBC		= 6;
	static const uint8_t SNDBC		= 7;
	static const uint8_t USBIRQ		= 13;
	static const uint8_t USBIEN		= 14;
	static const uint8_t USBCTL		= 15;
	static const uint8_t CPUCTL		= 16;
	static const uint8_t PINCTL		= 17;
	static const uint8_t REVISION	= 18;
	static const uint8_t IOPINS1	= 20;
	static const uint8_t IOPINS2	= 21;
	static const uint8_t GPINJIRQ	= 22;
	static const uint8_t GPINIEN	= 23;
	static const uint8_t GPINPOL	= 24;
	static const uint8_t HIRQ		= 25;
	static const uint8_t HIEN		= 26;
	static const uint8_t MODE		= 27;
	static const uint8_t PERADDR	= 28;
	static const uint8_t HCTL		= 29;
	static const uint8_t HXFR		= 30;
	static const uint8_t HRSL		= 31;

	// Bit definition for RCVBC register
	static const uint8_t RCVBC_BC0 = 0x01;

	uint8_t writeRegister(uint8_t address, uint8_t data);
	uint8_t writeBytes(uint8_t address, uint8_t *data, uint8_t length);
	uint8_t readRegister(uint8_t address, uint8_t *data);
	uint8_t readBytes(uint8_t address, uint8_t *data, uint8_t length);

private:
	Spi *spi;
};

#endif /* MAX3421E_H_ */

/*
 * Spi.h
 *
 *  Created on: Oct 13, 2009
 *      Author: fgervais
 */

#ifndef SPI_H_
#define SPI_H_

#include "Peripheral.h"

#include "stm32f10x.h"

class SpiConfiguration;

class Spi: public Peripheral {
public:
	static const uint16_t FULL_DUPLEX_2LINES = 0x0000;
	static const uint16_t RX_ONLY_2LINES	= 0x0400;
	static const uint16_t RX_1LINE			= 0x8000;
	static const uint16_t TX_1LINE			= 0xC000;
	static const uint16_t MASTER = 0;
	static const uint16_t SLAVE = 0;
	static const uint16_t FRAME_8BITS = 0;
	static const uint16_t FRAME_16BITS = 0;
	static const uint16_t LSB_FISRT = 0;
	static const uint16_t MSB_FIRST = 0;

	Spi(SPI_TypeDef *spiRegisters);
	virtual ~Spi();

	void configure(SpiConfiguration config);
	uint8_t readWrite(uint8_t data);
private :
	SPI_TypeDef *spiRegisters;
};

#endif /* SPI_H_ */

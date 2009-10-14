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
	static const uint32_t DUPLEX_HALF = 0;
	static const uint32_t DUPLEX_FULL = 0;
	static const uint32_t MASTER = 0;
	static const uint32_t SLAVE = 0;

	Spi(SPI_TypeDef *spiRegisters);
	virtual ~Spi();

	void configure(SpiConfiguration config);
	uint8_t readWrite(uint8_t data);
private :
	SPI_TypeDef *spiRegisters;
};

#endif /* SPI_H_ */

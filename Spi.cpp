/*
 * Spi.cpp
 *
 *  Created on: Oct 13, 2009
 *      Author: fgervais
 */

#include "Spi.h"

#include "stm32f10x.h"
#include "SpiConfiguration.h"

Spi::Spi(SPI_TypeDef *spiRegisters) {
	this->spiRegisters = spiRegisters;
}

Spi::~Spi() {

}

void Spi::configure(SpiConfiguration config) {
	uint16_t cr1 = 0;

	cr1 |= config.lineMode | config.frameFormat | config.slaveSelect |
		config.firstBit | config.prescaler | config.configuration |
		config.clockPolarity | config.clockPhase;

	spiRegisters->CR1 = cr1;

	// Enable SPI
	spiRegisters->CR1 |= SPI_CR1_SPE;

	// Select SPI mode
	spiRegisters->I2SPR &= ~(SPI_I2SCFGR_I2SMOD);
}

uint16_t Spi::readWrite(uint16_t data) {
	spiRegisters->DR = data;

	return spiRegisters->DR;
}

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

}

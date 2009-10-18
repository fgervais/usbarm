/*
 * Spi.cpp
 *
 *  Created on: Oct 13, 2009
 *      Author: fgervais
 */

#include "Spi.h"

#include "stm32f10x.h"
#include "SpiConfiguration.h"
#include "GpioPin.h"

Spi::Spi(uint8_t id, SPI_TypeDef *spiRegisters, GpioPin *slaveSelect) : Peripheral(id) {
	this->spiRegisters = spiRegisters;
	this->slaveSelect = slaveSelect;
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
	// Wait while transmit buffer is not empty
	while(!(spiRegisters->SR & SPI_SR_TXE))
	spiRegisters->DR = data;

	return spiRegisters->DR;
}

uint8_t Spi::readWrite(uint8_t data) {
	// Wait while transmit buffer is not empty
	while(!(spiRegisters->SR & SPI_SR_TXE))
	spiRegisters->DR = data;

	return spiRegisters->DR;
}

void Spi::selectSlave() {
	slaveSelect->setLow();
}

void Spi::unselectSlave() {
	slaveSelect->setHigh();
}

uint8_t Spi::isBusy() {
	return spiRegisters->SR & SPI_SR_BSY;
}

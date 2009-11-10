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

Spi::Spi(SPI_TypeDef *spiRegisters, uint8_t id, GpioPin *slaveSelect) : Peripheral(id) {
	this->spiRegisters = spiRegisters;
	this->slaveSelect = slaveSelect;

	// SS default high (see SPI standard)
	slaveSelect->setHigh();
}

Spi::~Spi() {

}

void Spi::configure(SpiConfiguration config) {
	uint16_t cr1 = 0;

	cr1 |= config.lineMode | config.frameFormat | config.slaveSelect |
		config.firstBit | config.prescaler | config.configuration |
		config.clockPolarity | config.clockPhase;

	spiRegisters->CR1 = cr1;

	// Select SPI mode
	spiRegisters->I2SCFGR &= ~(SPI_I2SCFGR_I2SMOD);

	// Enable SPI
	spiRegisters->CR1 |= SPI_CR1_SPE;
}

uint16_t Spi::readWrite(uint16_t data) {
	// Wait while transmit buffer is not empty
	while(!(spiRegisters->SR & SPI_SR_TXE));
	spiRegisters->DR = data;

	while(spiRegisters->SR & SPI_SR_BSY);
	return spiRegisters->DR;
}

uint8_t Spi::readWrite(uint8_t data) {
	return readWrite((uint16_t)data);
}

void Spi::write(uint16_t data) {
	// Wait while transmit buffer is not empty
	while(!(spiRegisters->SR & SPI_SR_TXE));
	spiRegisters->DR = data;
}

void Spi::write(uint8_t data) {
	write((uint16_t)data);
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

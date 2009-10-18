/*
 * MAX3421E.cpp
 *
 *  Created on: Oct 13, 2009
 *      Author: fgervais
 */

#include "MAX3421E.h"

#include "Spi.h"

MAX3421E::MAX3421E(Spi *spi) {
	this->spi = spi;
}

MAX3421E::~MAX3421E() {

}

/**
 * @brief Write data to the specified register address.
 * @param address Address of the register to write to.
 * @param data Data to write to the register.
 * @return Status bits.
 */
uint8_t MAX3421E::writeRegister(uint8_t address, uint8_t data) {
	return writeBytes(address, &data, 1);
}

/**
 * @brief Write multiple bytes to the MAX3421E.
 *
 * Depending of the specified register address. The MAX3421E is
 * going to have specific behavior. For example, multiple access
 * to the FIFOs freeze the internal MAX3421E register address.
 *
 * @see MAX3421E datasheet for more informations.
 *
 * @param address Register address of the first byte.
 * @param data Array of bytes to write.
 * @param length Number of bytes in the array.
 * @return Status bits.
 */
uint8_t MAX3421E::writeBytes(uint8_t address, uint8_t *data, uint8_t length) {
	uint8_t status;

	// For more information on command format, see MAX3421E datasheet
	uint8_t command = address << 3;
	// Direction bit = 1 (write)
	command |= 0x02;

	spi->selectSlave();
	// While the command is clocked in, the status bits are clocked out
	status = spi->readWrite(command);

	for(uint8_t i=0; i<length; i++) {
		spi->readWrite(data[i]);
	}

	// Wait until spi is finished with the transmission
	while(spi->isBusy());
	spi->unselectSlave();

	return 0;
}

/**
 * @brief Read a register.
 * @param address Address of the register to read.
 * @param data Pointer used to return the register value.
 * @return Status bits.
 */
uint8_t MAX3421E::readRegister(uint8_t address, uint8_t *data) {
	return 0;
}

/**
 * @brief Read multiple bytes of the MAX3421E.
 * @param address Register address of the first byte.
 * @param data Array used to return the bytes read.
 * @param length Number of byte to read.
 * @return Status bits.
 */
uint8_t MAX3421E::readBytes(uint8_t address, uint8_t *data, uint8_t length) {
	return 0;
}

/*
 * MAX3421E.cpp
 *
 *  Created on: Oct 13, 2009
 *      Author: fgervais
 */

#include "MAX3421E.h"

MAX3421E::MAX3421E() {

}

MAX3421E::~MAX3421E() {

}

/**
 * @brief Write data to the specified register address.
 * @param address Address of the register to write to.
 * @param data Data to write to the register.
 */
void writeRegister(uint8_t address, uint8_t data) {

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
 */
void writeBytes(uint8_t address, uint8_t *data, uint8_t length) {

}

/**
 * @brief Read a register.
 * @param address Address of the register to read.
 * @return Value of the register read.
 */
uint8_t readRegister(uint8_t address) {
	return 0;
}

/**
 * @brief Read multiple bytes of the MAX3421E.
 * @param address Register address of the first byte.
 * @param data Array used to return the bytes read.
 * @param length Number of byte to read.
 * @return
 */
uint8_t readBytes(uint8_t address, uint8_t *data, uint8_t length) {
	return 0;
}

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

	uint8_t writeRegister(uint8_t address, uint8_t data);
	uint8_t writeBytes(uint8_t address, uint8_t *data, uint8_t length);
	uint8_t readRegister(uint8_t address, uint8_t *data);
	uint8_t readBytes(uint8_t address, uint8_t *data, uint8_t length);

private:
	Spi *spi;
};

#endif /* MAX3421E_H_ */

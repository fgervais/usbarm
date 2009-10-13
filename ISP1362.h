/*
 * ISP1362.h
 *
 *  Created on: Oct 13, 2009
 *      Author: fgervais
 */

#ifndef ISP1362_H_
#define ISP1362_H_

#include <stdint.h>

class ISP1362 {
public:
	ISP1362();
	virtual ~ISP1362();

	uint16_t read(uint16_t address);
	void write(uint16_t address, uint16_t data);
};

#endif /* ISP1362_H_ */

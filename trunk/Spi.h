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
	static const uint16_t FULL_DUPLEX_2LINES	= 0x0000; /** 2-line unidirectional data, Full duplex (transmit and receive) */
	static const uint16_t RX_ONLY_2LINES	 	= 0x0400; /** 2-line unidirectional data, Output disabled (receive-only mode) */
	static const uint16_t RX_1LINE				= 0x8000; /** 1-line bidirectional data, Output disabled (receive-only mode) */
	static const uint16_t TX_1LINE				= 0xC000; /** 1-line bidirectional data, Output enabled (receive-only mode) */
	static const uint16_t FRAME_8BITS			= 0x0000; /** 8-bit data frame format is selected for transmission/reception */
	static const uint16_t FRAME_16BITS			= 0x0800; /** 16-bit data frame format is selected for transmission/reception */
	static const uint16_t SOFTWARE_SLAVESELECT	= 0x0200; /** Software slave management enabled */
	static const uint16_t HARDWARE_SLAVESELECT	= 0x0000; /** Software slave management disabled */
	static const uint16_t LSB_FISRT 			= 0x0080; /** LSB transmitted first */
	static const uint16_t MSB_FIRST				= 0x0000; /** MSB transmitted first */
	static const uint16_t CLOCK_PRESCALER_2		= 0x0000; /** fPCLK/2 */
	static const uint16_t CLOCK_PRESCALER_4		= 0x0008; /** fPCLK/4 */
	static const uint16_t CLOCK_PRESCALER_8		= 0x0010; /** fPCLK/8 */
	static const uint16_t CLOCK_PRESCALER_16	= 0x0018; /** fPCLK/16 */
	static const uint16_t CLOCK_PRESCALER_32	= 0x0020; /** fPCLK/32 */
	static const uint16_t CLOCK_PRESCALER_64	= 0x0028; /** fPCLK/64 */
	static const uint16_t CLOCK_PRESCALER_128	= 0x0030; /** fPCLK/128 */
	static const uint16_t CLOCK_PRESCALER_256	= 0x0038; /** fPCLK/256 */
	static const uint16_t MASTER				= 0x0104; /** Master configuration */
	static const uint16_t SLAVE					= 0x0000; /** Slave configuration */
	static const uint16_t CLOCK_POLARITY_LOW	= 0x0000; /** CK to 0 when idle */
	static const uint16_t CLOCK_POLARITY_HIGH	= 0x0002; /** CK to 1 when idle */
	static const uint16_t CLOCK_PHASE_EDGE1		= 0x0000; /** The first clock transition is the first data capture edge */
	static const uint16_t CLOCK_PHASE_EDGE2		= 0x0001; /** The second clock transition is the first data capture edge */

	Spi(SPI_TypeDef *spiRegisters);
	virtual ~Spi();

	void configure(SpiConfiguration config);
	uint8_t readWrite(uint8_t data);
private :
	SPI_TypeDef *spiRegisters;
};

#endif /* SPI_H_ */

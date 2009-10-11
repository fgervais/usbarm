/*
 * Uart.cpp
 *
 *  Created on: 2009-09-29
 *      Author: oex
 */

#include "Uart.h"
#include "UartConfiguration.h"

Uart::Uart(USART_TypeDef *uartRegisters, uint32_t clockFrequency) {
	this->uartRegisters = uartRegisters;
	this->clockFrequency = clockFrequency;
}

Uart::~Uart() {

}


void Uart::sendInterrupt() {

}

void Uart::receiveInterrupt() {

}

void Uart::write(char* data, uint16_t lenght){

	for (int8_t i=0; i < lenght && data[i]; i++)
	{
		charBuffer.push(data[i]);
	}


	while(!charBuffer.empty())
	{
		//waiting for the data to be transfert in the TransmitDataRegister
		while(!(uartRegisters->SR & UART_TX_DATA_REGISTER));
		uartRegisters->DR = charBuffer.front();
		charBuffer.pop();
	}
}

char Uart::read(uint8_t lenght){
	//char test = 'a';
	return (uartRegisters->SR & 0x00000040) >> 6;
}


uint16_t Uart::calculateBRR(uint16_t baudrate){
	uint32_t mantisse = 0, tmpreg = 0, fractional = 0;

	/**             fck = 72000000MHz
	    baudrate =  -----------------
	                 (16 * USARTDIV)
	*/

	/*	USARTDIV = 937.5, Fraction = 16 * 0.5 = 8 = 0x8,
		Mantisse = 937 = 0x3A9, BRR = 0x00003A9C  */

	mantisse = ((0x19 * this->clockFrequency) / (0x04 * (baudrate)));
	tmpreg = (mantisse / 0x64) << 0x04;

	fractional = mantisse - (0x64 * (tmpreg >> 0x04));
	tmpreg |= ((((fractional * 0x10) + 0x32) / 0x64)) & ((uint8_t)0x0F);

	return (uint16_t)tmpreg;
}

void Uart::configure(UartConfiguration config){


	uartRegisters->BRR = calculateBRR(config.baudrate);

	uartRegisters->CR1 |= config.wordLenght | config.parityEnable | config.parityType;
	uartRegisters->CR1 |= UART_ENABLE | UART_TX_ENABLE | UART_RX_ENABLE;

	uartRegisters->CR2 |= config.stopBit;
}


/*
 * Uart.cpp
 *
 *  Created on: 2009-09-29
 *      Author: oex
 */


#include "Uart.h"
#include "UartConfiguration.h"
#include "Gpio.h"
#include "GpioPin.h"

#include "STM32F103.h"

Uart::Uart(USART_TypeDef *uartRegisters, uint8_t id,
		PeripheralType type, uint32_t PCLK1_Frequency) : Peripheral (id, type) {
	this->uartRegisters = uartRegisters;
	this->clockFrequency = clockFrequency;
	this->txQueue = new Queue<char>(200);

}

Uart::~Uart() {
	/* Free memory */
	delete txQueue;
}


void Uart::sendInterrupt() {
}

void Uart::receiveInterrupt() {
}

void Uart::poll(void) {


	if (!txQueue->isEmpty()) {
		if (uartRegisters->SR & UART_TX_DATA_REGISTER) {
			uartRegisters->DR = txQueue->getElement();
		}
	}

	if (uartRegisters->SR & UART_RX_DATA_REGISTER) {

		txQueue->addElement('r');
		txQueue->addElement('e');
		txQueue->addElement('c');
		txQueue->addElement('u');
		txQueue->addElement(':');
		txQueue->addElement(' ');
		txQueue->addElement(uartRegisters->DR);
		txQueue->addElement('\r');


		uartRegisters->SR &= ~UART_RX_DATA_REGISTER;
	}
}

void Uart::write(char* data, uint16_t length) {
	for (uint8_t i = 0; i < length; i++) {
		txQueue->addElement(data[i]);
	}
}

char Uart::read(uint8_t lenght){

	return (uartRegisters->SR & 0x00000040) >> 6;
}


uint16_t Uart::calculateBRR(uint16_t baudrate){
	uint32_t mantisse = 0, tmpreg = 0, fractional = 0;

	/**             fck = 72000000MHz
	    baudrate =  -----------------
	                 (16 * USARTDIV)
	*/

	/*	USARTDIV = 478.75, Fraction = 16 * 0.75 = 11.68 = 0xC,
		Mantisse = 478 = 0x1DEC, BRR = 0x00001DEC  */

	mantisse = ((0x19 * this->clockFrequency) / (0x04 * (baudrate)));
	tmpreg = (mantisse / 0x64) << 0x04;

	fractional = mantisse - (0x64 * (tmpreg >> 0x04));
	tmpreg |= ((((fractional * 0x10) + 0x32) / 0x64)) & ((uint8_t)0x0F);

	return (uint16_t)tmpreg;
}

void Uart::configure(UartConfiguration config){
	uartRegisters->BRR = calculateBRR(config.baudrate);
	//uartRegisters->BRR = 0x1D4C;

	uartRegisters->CR1 |= config.wordLenght | config.parityEnable | config.parityType;
	uartRegisters->CR1 |= UART_ENABLE | UART_TX_ENABLE | UART_RX_ENABLE;

	uartRegisters->CR2 |= config.stopBit;
	uartRegisters->SR &= ~UART_RX_DATA_REGISTER;
}


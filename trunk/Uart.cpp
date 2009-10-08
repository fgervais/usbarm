/*
 * Uart.cpp
 *
 *  Created on: 2009-09-29
 *      Author: oex
 */

#include "Uart.h"
#include "UartConfiguration.h"

Uart::Uart(USART_TypeDef *uartRegisters) {
	this->uartRegisters = uartRegisters;
}

Uart::~Uart() {

}


void Uart::sendInterrupt() {

}

void Uart::receiveInterrupt() {

}

void Uart::write(char *data, uint8_t lenght){
	uartRegisters->DR = *data;

}

char Uart::read(uint8_t lenght){
	char test = 'a';
	return test;
}


void Uart::configure(UartConfiguration config){
	uartRegisters->BRR = config.baudrate;

	uartRegisters->CR1 |= config.wordLenght | config.parityEnable | config.parityType;
	uartRegisters->CR1 |= UART_ENABLE | UART_TX_ENABLE | UART_RX_ENABLE;

	uartRegisters->CR2 |= config.stopBit;
}


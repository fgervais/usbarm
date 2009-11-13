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
#include "Queue.h"

#include "STM32F103.h"

Uart::Uart(USART_TypeDef *uartRegisters, uint8_t id,
		uint32_t PCLK1_Frequency) {
	this->uartRegisters = uartRegisters;
	this->clockFrequency = clockFrequency;
	this->txQueue = new Queue<char>(200);
	//this->rxQueue = new Queue<char>(200);
}

Uart::~Uart() {
	/* Free memory */
	//delete rxQueue;
	delete txQueue;
}


void Uart::sendInterrupt() {
}

void Uart::receiveInterrupt() {
}

void Uart::poll(void) {
	char data;
	// if some data are present in the send Queue,
	// write the first char in the transmit data register
	if (!txQueue->isEmpty()) {
		if (uartRegisters->SR & UART_TX_DATA_REGISTER) {
			uartRegisters->DR = txQueue->getElement();
		}
	}

	// if some data are present in the receive data register
	// put it in the receive Queue
	if (uartRegisters->SR & UART_RX_DATA_REGISTER) {
		data = uartRegisters->DR;
		//rxQueue->addElement(data);
		txQueue->addElement(data); // echo

		//uartRegisters->SR &= ~UART_RX_DATA_REGISTER;
	}
}

void Uart::write(char* data, uint16_t length) {
	//insert data in the txQueue
	for (uint16_t i = 0; i < length; i++) {
		txQueue->addElement(data[i]);
	}
}

char Uart::read(){
	char data = -1;
	// if some data are present in the receive Queue
	// return the first char in the queue
	//if (!rxQueue->isEmpty())
		//data = rxQueue->getElement();

	return data;
}


uint16_t Uart::calculateBRR(uint16_t baudrate){
	uint32_t mantisse = 0, tmpreg = 0, fractional = 0;

	// this calculation is explicated in
	// the Software Reference manuel page 665, 666


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
	// set baudrate
	//uartRegisters->BRR = calculateBRR(config.baudrate);
	uartRegisters->BRR = 0x1D4C;

	// set wordLenght, parity, UartEnable, UartTxEnable UartRxEnable
	uartRegisters->CR1 |= config.wordLenght | config.parityEnable | config.parityType;
	uartRegisters->CR1 |= UART_ENABLE | UART_TX_ENABLE | UART_RX_ENABLE;

	// set stopbit
	uartRegisters->CR2 |= config.stopBit;

	// usefull?
	//uartRegisters->SR &= ~UART_RX_DATA_REGISTER;
}


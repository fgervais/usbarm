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


void Uart::configure(UartConfiguration config){
	//uint32_t configRegister = 0;
	//uartRegisters->

}


/*
 * STM32F103.cpp
 *
 *  Created on: Oct 1, 2009
 *      Author: fgervais
 */

#include "STM32F103.h"

#include "Uart.h"
#include "Gpio.h"

#include "stm32f10x.h"

/* Static init. Required to make the compiler happy */
Uart* STM32F103::uart1 = 0;
Uart* STM32F103::uart2 = 0;
Gpio* STM32F103::gpioA = 0;


STM32F103::STM32F103() {

}

STM32F103::~STM32F103() {

}

/**
 * @brief	This function return an instance to the actual Uart1.
 * @return	The STM32F103 Uart1
 */
Uart* STM32F103::getUart1() {
	systemClocksFreq systemClock;

	getRccClockFreq(&systemClock);

	if(uart1 == 0) {
		uart1 = new Uart(USART1, systemClock.PCLK2_Frequency);
		// Send clock to USART 1
		RCC->APB2ENR |= RCC_APB2ENR_USART1EN | RCC_APB2ENR_AFIOEN;
	}
	return uart1;
}



/**
 * @brief	This function return an instance to the actual Uart1.
 * @return	The STM32F103 Uart1
 */
Uart* STM32F103::getUart2() {
	systemClocksFreq systemClock;


	getRccClockFreq(&systemClock);

	if(uart2 == 0) {
		uart2 = new Uart(USART2, systemClock.PCLK1_Frequency);
		// Send clock to USART 2
		RCC->APB2ENR |= RCC_APB2ENR_USART1EN | RCC_APB2ENR_AFIOEN;
	}
	return uart2;
}


Gpio* STM32F103::getGpioA() {
	if(gpioA == 0) {
		gpioA = new Gpio(GPIOA);
		// Send clock to GPIO A
		RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	}
	return gpioA;
}



/**
  * @brief  Returns the frequencies of different on chip clocks.
  * @param  RCC_Clocks: pointer to a RCC_ClocksTypeDef structure which will hold
  *   the clocks frequencies.
  * @retval None
  */
void STM32F103::getRccClockFreq(systemClocksFreq* systemClock) {
  uint32_t tmp = 0, pllmull = 0, pllsource = 0, presc = 0;

  /* Get SYSCLK source -------------------------------------------------------*/
  tmp = RCC->CFGR & CFGR_SWS_Mask;

  switch (tmp)
  {
    case 0x00:  /* HSI used as system clock */
    	systemClock->SYSCLK_Frequency = HSI_Value;
      break;
    case 0x04:  /* HSE used as system clock */
    	systemClock->SYSCLK_Frequency = HSE_Value;
      break;
    case 0x08:  /* PLL used as system clock */

      /* Get PLL clock source and multiplication factor ----------------------*/
      pllmull = RCC->CFGR & CFGR_PLLMull_Mask;
      pllsource = RCC->CFGR & CFGR_PLLSRC_Mask;

      pllmull = ( pllmull >> 18) + 2;

      if (pllsource == 0x00)
      {/* HSI oscillator clock divided by 2 selected as PLL clock entry */
    	  systemClock->SYSCLK_Frequency = (HSI_Value >> 1) * pllmull;
      }
      else
      {/* HSE selected as PLL clock entry */
        if ((RCC->CFGR & CFGR_PLLXTPRE_Mask) != (uint32_t)RESET)
        {/* HSE oscillator clock divided by 2 */
        	systemClock->SYSCLK_Frequency = (HSE_Value >> 1) * pllmull;
        }
        else
        {
        	systemClock->SYSCLK_Frequency = HSE_Value * pllmull;
        }
      }
      break;

    default:
    	systemClock->SYSCLK_Frequency = HSI_Value;
      break;
  }

  /* Compute HCLK, PCLK1, PCLK2 and ADCCLK clocks frequencies ----------------*/
  /* Get HCLK prescaler */
  tmp = RCC->CFGR & CFGR_HPRE_Set_Mask;
  tmp = tmp >> 4;
  presc = APBAHBPrescTable[tmp];
  /* HCLK clock frequency */
  systemClock->HCLK_Frequency = systemClock->SYSCLK_Frequency >> presc;
  /* Get PCLK1 prescaler */
  tmp = RCC->CFGR & CFGR_PPRE1_Set_Mask;
  tmp = tmp >> 8;
  presc = APBAHBPrescTable[tmp];
  /* PCLK1 clock frequency */
  systemClock->PCLK1_Frequency = systemClock->HCLK_Frequency >> presc;
  /* Get PCLK2 prescaler */
  tmp = RCC->CFGR & CFGR_PPRE2_Set_Mask;
  tmp = tmp >> 11;
  presc = APBAHBPrescTable[tmp];
  /* PCLK2 clock frequency */
  systemClock->PCLK2_Frequency = systemClock->HCLK_Frequency >> presc;
  /* Get ADCCLK prescaler */
  tmp = RCC->CFGR & CFGR_ADCPRE_Set_Mask;
  tmp = tmp >> 14;
  presc = ADCPrescTable[tmp];
  /* ADCCLK clock frequency */
  systemClock->ADCCLK_Frequency = systemClock->PCLK2_Frequency / presc;
}

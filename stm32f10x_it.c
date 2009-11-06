/**
  ******************************************************************************
  * @file    Project/Template/stm32f10x_it.c
  * @author  MCD Application Team
  * @version V3.1.0
  * @date    06/19/2009
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2009 STMicroelectronics</center></h2>
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"

#include "STM32F103.h"
#include "Uart.h"
#include "Gpio.h"
#include "GpioPin.h"
#include "Timer.h"

/** @addtogroup Template_Project
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief   This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
 * @brief	This function handle the USART1 interrupt request.
 * @param	None
 * @retval	None
 */
void USART1_IRQHandler(void)
{
	// Data received?
	STM32F103::getUart1()->receiveInterrupt();

	// Data sent?
	STM32F103::getUart1()->sendInterrupt();
}

/**
 * @brief	This function handle the EXT0 interrupt request.
 * @param	None
 * @retval	None
 */
void EXTI0_IRQHandler(void) {
	uint8_t exti;
	/* Check which port is linked to that interrupt */
	// Right shift four time "pin number"
	exti = (AFIO->EXTICR[0] & 0x000F);

	switch(exti) {
	case 0:
		STM32F103::getGpioA()->getPin(0)->extInterrupt();
		break;
	case 1:
		STM32F103::getGpioB()->getPin(0)->extInterrupt();
		break;
	case 2:
		STM32F103::getGpioC()->getPin(0)->extInterrupt();
		break;
	case 3:
		STM32F103::getGpioD()->getPin(0)->extInterrupt();
		break;
	}

	// Clear interrupt pending bit
	EXTI->PR |= EXTI_PR_PR0;
}

/**
 * @brief	This function handle the EXT1 interrupt request.
 * @param	None
 * @retval	None
 */
void EXTI1_IRQHandler(void) {
	uint8_t exti;
	/* Check which port is linked to that interrupt */
	// Right shift four time "pin number"
	exti = ((AFIO->EXTICR[0] >> 4) & 0x000F);

	switch(exti) {
	case 0:
		STM32F103::getGpioA()->getPin(1)->extInterrupt();
		break;
	case 1:
		STM32F103::getGpioB()->getPin(1)->extInterrupt();
		break;
	case 2:
		STM32F103::getGpioC()->getPin(1)->extInterrupt();
		break;
	case 3:
		STM32F103::getGpioD()->getPin(1)->extInterrupt();
		break;
	}

	// Clear interrupt pending bit
	EXTI->PR |= EXTI_PR_PR1;
}

/**
 * @brief	This function handle the EXT2 interrupt request.
 * @param	None
 * @retval	None
 */
void EXTI2_IRQHandler(void) {
	uint8_t exti;
	/* Check which port is linked to that interrupt */
	// Right shift four time "pin number"
	exti = ((AFIO->EXTICR[0] >> 8) & 0x000F);

	switch(exti) {
	case 0:
		STM32F103::getGpioA()->getPin(2)->extInterrupt();
		break;
	case 1:
		STM32F103::getGpioB()->getPin(2)->extInterrupt();
		break;
	case 2:
		STM32F103::getGpioC()->getPin(2)->extInterrupt();
		break;
	case 3:
		STM32F103::getGpioD()->getPin(2)->extInterrupt();
		break;
	}

	// Clear interrupt pending bit
	EXTI->PR |= EXTI_PR_PR2;
}

/**
 * @brief	This function handle the EXT3 interrupt request.
 * @param	None
 * @retval	None
 */
void EXTI3_IRQHandler(void) {
	uint8_t exti;
	/* Check which port is linked to that interrupt */
	// Right shift four time "pin number"
	exti = ((AFIO->EXTICR[0] >> 12) & 0x000F);

	switch(exti) {
	case 0:
		STM32F103::getGpioA()->getPin(3)->extInterrupt();
		break;
	case 1:
		STM32F103::getGpioB()->getPin(3)->extInterrupt();
		break;
	case 2:
		STM32F103::getGpioC()->getPin(3)->extInterrupt();
		break;
	case 3:
		STM32F103::getGpioD()->getPin(3)->extInterrupt();
		break;
	}

	// Clear interrupt pending bit
	EXTI->PR |= EXTI_PR_PR3;
}

/**
 * @brief	This function handle the EXT4 interrupt request.
 * @param	None
 * @retval	None
 */
void EXTI4_IRQHandler(void) {
	uint8_t exti;
	/* Check which port is linked to that interrupt */
	// Right shift four time "pin number"
	exti = (AFIO->EXTICR[1] & 0x000F);

	switch(exti) {
	case 0:
		STM32F103::getGpioA()->getPin(4)->extInterrupt();
		break;
	case 1:
		STM32F103::getGpioB()->getPin(4)->extInterrupt();
		break;
	case 2:
		STM32F103::getGpioC()->getPin(4)->extInterrupt();
		break;
	case 3:
		STM32F103::getGpioD()->getPin(4)->extInterrupt();
		break;
	}

	// Clear interrupt pending bit
	EXTI->PR |= EXTI_PR_PR4;
}

/**
 * @brief	This function handle the EXT9_5 interrupt request.
 * @param	None
 * @retval	None
 */
void EXTI9_5_IRQHandler(void) {
	uint8_t exti;
	uint8_t extiPin;
	// Check which external interrupt triggered
	if(EXTI->PR & EXTI_PR_PR5) {
		/* Check which port is linked to that interrupt */
		// Right shift four time "pin number"
		exti = ((AFIO->EXTICR[1] >> 4) & 0x000F);
		extiPin = 5;
	}
	else if(EXTI->PR & EXTI_PR_PR6) {
		exti = ((AFIO->EXTICR[1] >> 8) & 0x000F);
		extiPin = 6;
	}
	else if(EXTI->PR & EXTI_PR_PR7) {
		exti = ((AFIO->EXTICR[1] >> 12) & 0x000F);
		extiPin = 7;
	}
	else if(EXTI->PR & EXTI_PR_PR8) {
		exti = (AFIO->EXTICR[2] & 0x000F);
		extiPin = 8;
	}
	else if(EXTI->PR & EXTI_PR_PR9) {
		exti = ((AFIO->EXTICR[2] >> 4) & 0x000F);
		extiPin = 9;
	}

	switch(exti) {
	case 0:
		STM32F103::getGpioA()->getPin(extiPin)->extInterrupt();
		break;
	case 1:
		STM32F103::getGpioB()->getPin(extiPin)->extInterrupt();
		break;
	case 2:
		STM32F103::getGpioC()->getPin(extiPin)->extInterrupt();
		break;
	case 3:
		STM32F103::getGpioD()->getPin(extiPin)->extInterrupt();
		break;
	}

	// Clear interrupt pending bit
	EXTI->PR |= (1 << extiPin);
}

/**
 * @brief	This function handle the EXT15_10 interrupt request.
 * @param	None
 * @retval	None
 */
void EXTI15_10_IRQHandler(void) {
	uint8_t exti;
	uint8_t extiPin;
	// Check which external interrupt triggered
	if(EXTI->PR & EXTI_PR_PR10) {
		/* Check which port is linked to that interrupt */
		// Right shift four time "pin number"
		exti = ((AFIO->EXTICR[2] >> 8) & 0x000F);
		extiPin = 10;
	}
	else if(EXTI->PR & EXTI_PR_PR11) {
		exti = ((AFIO->EXTICR[2] >> 12) & 0x000F);
		extiPin = 11;
	}
	else if(EXTI->PR & EXTI_PR_PR12) {
		exti = (AFIO->EXTICR[3] & 0x000F);
		extiPin = 12;
	}
	else if(EXTI->PR & EXTI_PR_PR13) {
		exti = ((AFIO->EXTICR[3] >> 4) & 0x000F);
		extiPin = 13;
	}
	else if(EXTI->PR & EXTI_PR_PR14) {
		exti = ((AFIO->EXTICR[3] >> 8) & 0x000F);
		extiPin = 14;
	}
	else if(EXTI->PR & EXTI_PR_PR15) {
		exti = ((AFIO->EXTICR[3] >> 12) & 0x000F);
		extiPin = 15;
	}

	switch(exti) {
	case 0:
		STM32F103::getGpioA()->getPin(extiPin)->extInterrupt();
		break;
	case 1:
		STM32F103::getGpioB()->getPin(extiPin)->extInterrupt();
		break;
	case 2:
		STM32F103::getGpioC()->getPin(extiPin)->extInterrupt();
		break;
	case 3:
		STM32F103::getGpioD()->getPin(extiPin)->extInterrupt();
		break;
	}

	// Clear interrupt pending bit
	EXTI->PR |= (1 << extiPin);
}

/**
 * @brief	This function handle the TIM2_IRQHandler interrupt request.
 * @param	None
 * @retval	None
 */
void TIM2_IRQHandler(void) {
	if(TIM2->SR & TIM_SR_UIF) {
		STM32F103::getTimer2()->overflowInterrupt();
	}
}

/**
  * @}
  */


/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/

/*
 * STM32F103.h
 *
 *  Created on: Oct 1, 2009
 *      Author: fgervais
 */

#ifndef STM32F103_H_
#define STM32F103_H_

#include "Microcontroller.h"
#include "stm32f10x.h"

static __I uint8_t APBAHBPrescTable[16] = {0, 0, 0, 0, 1, 2, 3, 4, 1, 2, 3, 4, 6, 7, 8, 9};
static __I uint8_t ADCPrescTable[4] = {2, 4, 6, 8};

#define CFGR_PLLMull_Mask         ((uint32_t)0x003C0000)
#define CFGR_PLLSRC_Mask          ((uint32_t)0x00010000)
#define CFGR_PLLXTPRE_Mask        ((uint32_t)0x00020000)
#define CFGR_SWS_Mask             ((uint32_t)0x0000000C)
#define CFGR_SW_Mask              ((uint32_t)0xFFFFFFFC)
#define CFGR_HPRE_Reset_Mask      ((uint32_t)0xFFFFFF0F)
#define CFGR_HPRE_Set_Mask        ((uint32_t)0x000000F0)
#define CFGR_PPRE1_Reset_Mask     ((uint32_t)0xFFFFF8FF)
#define CFGR_PPRE1_Set_Mask       ((uint32_t)0x00000700)
#define CFGR_PPRE2_Reset_Mask     ((uint32_t)0xFFFFC7FF)
#define CFGR_PPRE2_Set_Mask       ((uint32_t)0x00003800)
#define CFGR_ADCPRE_Reset_Mask    ((uint32_t)0xFFFF3FFF)
#define CFGR_ADCPRE_Set_Mask      ((uint32_t)0x0000C000)



typedef struct
{
  uint8_t NVIC_IRQChannel;                    /*!< Specifies the IRQ channel to be enabled or disabled.
                                                   This parameter can be a value of @ref IRQn_Type
                                                   (For the complete STM32 Devices IRQ Channels list, please
                                                    refer to stm32f10x.h file) */

  uint8_t NVIC_IRQChannelPreemptionPriority;  /*!< Specifies the pre-emption priority for the IRQ channel
                                                   specified in NVIC_IRQChannel. This parameter can be a value
                                                   between 0 and 15 as described in the table @ref NVIC_Priority_Table */

  uint8_t NVIC_IRQChannelSubPriority;         /*!< Specifies the subpriority level for the IRQ channel specified
                                                   in NVIC_IRQChannel. This parameter can be a value
                                                   between 0 and 15 as described in the table @ref NVIC_Priority_Table */

  FunctionalState NVIC_IRQChannelCmd;         /*!< Specifies whether the IRQ channel defined in NVIC_IRQChannel
                                                   will be enabled or disabled.
                                                   This parameter can be set either to ENABLE or DISABLE */
} NVIC_InitTypeDef;


typedef struct
{
	  uint32_t SYSCLK_Frequency;  /*!< returns SYSCLK clock frequency expressed in Hz */
	  uint32_t HCLK_Frequency;    /*!< returns HCLK clock frequency expressed in Hz */
	  uint32_t PCLK1_Frequency;   /*!< returns PCLK1 clock frequency expressed in Hz */
	  uint32_t PCLK2_Frequency;   /*!< returns PCLK2 clock frequency expressed in Hz */
	  uint32_t ADCCLK_Frequency;  /*!< returns ADCCLK clock frequency expressed in Hz */
} systemClocksFreq;

class Uart;
class Gpio;
class Spi;
class Usb;

class STM32F103: public Microcontroller {
public:
	STM32F103();
	virtual ~STM32F103();

	static Uart* getUart1();
	static Uart* getUart2();
	static Gpio* getGpioA();
	static Spi* getSpi1();

private:

	static Uart *uart1;
	static Uart *uart2;
	static Gpio *gpioA;
	static Spi *spi1;
	static Usb *usb;

	static void NVIC_Init(NVIC_InitTypeDef* NVIC_InitStruct);
	static void getRccClockFreq(systemClocksFreq* systemClock);
};

#endif /* STM32F103_H_ */

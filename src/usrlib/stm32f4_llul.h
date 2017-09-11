/**
 * Библиотека инлайн функций для работы с регистрами
 * llul - low layer user lib
 */
#include "stm32f4_bf.h"

#ifndef STM32F4_LLUL_H
#define STM32F4_LLUL_H

#define SET_MASK(REG, MASK)		((REG) |= (MASK))
#define CLEAR_MASK(REG, MASK)	((REG) &= ~(MASK))

/*****************************************************************************
 *		RCC
 ****************************************************************************/

inline void RCC_HSEon (void)
{
	extern volatile RCC_CR_t* RCC_CR;
	RCC_CR->HSEON = 1;
}

inline void RCC_WaitHSEready (void)
{
	extern volatile RCC_CR_t* RCC_CR;
	while (RCC_CR->HSERDY != 1) { }
}

inline void RCC_PLLon (void)
{
	extern volatile RCC_CR_t* RCC_CR;
	RCC_CR->PLLON = 1;
}

inline void RCC_WaitPLLready (void)
{
	extern volatile RCC_CR_t* RCC_CR;
	while (RCC_CR->PLLRDY != 1) { }
}

inline void RCC_SetAHBprescaler (eAHBprescaler_t prescaler)
{
	extern volatile RCC_CFGR_t* RCC_CFGR;
	RCC_CFGR->HPRE = prescaler;
}

inline void RCC_SetAPB1prescaler (volatile eAPBprescaler_t APB1prescaler)
{
	extern volatile RCC_CFGR_t* RCC_CFGR;
	RCC_CFGR->PPRE1 = APB1prescaler;
}

inline void RCC_SetAPB2prescaler (volatile eAPBprescaler_t APB2prescaler)
{
	extern volatile RCC_CFGR_t* RCC_CFGR;
	RCC_CFGR->PPRE2 = APB2prescaler;
}

inline void RCC_SystemClockSwitch (eSystemClockSwitch_t var)
{
	extern volatile RCC_CFGR_t* RCC_CFGR;
	RCC_CFGR->SW = var;
}

// 2 ≤ var ≤ 63
inline void RCC_SetPLLM (uint8_t var)
{
	extern volatile RCC_PLLCFGR_t* RCC_PLLCFGR;
	RCC_PLLCFGR->PLLM = var;
}

// 50 ≤ var ≤ 432
inline void RCC_SetPLLN (uint16_t var)
{
	extern volatile RCC_PLLCFGR_t* RCC_PLLCFGR;
	RCC_PLLCFGR->PLLN = var;
}

inline void RCC_SetPLLP (ePLLPdiv_t div)
{
	extern volatile RCC_PLLCFGR_t* RCC_PLLCFGR;
	RCC_PLLCFGR->PLLP = div;
}

// 2 ≤ var ≤ 15
inline void RCC_SetPLLQ (uint16_t var)
{
	extern volatile RCC_PLLCFGR_t* RCC_PLLCFGR;
	RCC_PLLCFGR->PLLQ = var;
}

inline void RCC_SetPLLsource (ePLLsource_t source)
{
	extern volatile RCC_PLLCFGR_t* RCC_PLLCFGR;
	RCC_PLLCFGR->PLLSRC = source;
}

inline void RCC_PortClockEnable (GPIO_TypeDef* Port)
{
	extern volatile RCC_AHB1ENR_t* RCC_AHB1ENR;
	if (Port == GPIOA) {
		RCC_AHB1ENR->GPIOAEN = 1;
	} else if (Port == GPIOB) {
		RCC_AHB1ENR->GPIOBEN = 1;
	} else if (Port == GPIOC) {
		RCC_AHB1ENR->GPIOCEN = 1;
	} else if (Port == GPIOD) {
		RCC_AHB1ENR->GPIODEN = 1;
	} else if (Port == GPIOE) {
		RCC_AHB1ENR->GPIOEEN = 1;
	} else if (Port == GPIOF) {
		RCC_AHB1ENR->GPIOFEN = 1;
	} else if (Port == GPIOG) {
		RCC_AHB1ENR->GPIOGEN = 1;	
	} else if (Port == GPIOH) {
		RCC_AHB1ENR->GPIOHEN = 1;
	} else if (Port == GPIOI) {
		RCC_AHB1ENR->GPIOIEN = 1;
	}
}

/*****************************************************************************
 *		FLASH
 ****************************************************************************/
inline void FLASH_SetLatency (eLatency_t Latency)
{
	extern volatile FLASH_ACR_t* FLASH_ACR;
	FLASH_ACR->LATENCY = Latency;
}

/*****************************************************************************
 *		GPIO
 ****************************************************************************/

inline void GPIO_SetModer (GPIO_TypeDef* Port, uint8_t Pin, eMode_t Mode)
{
	CLEAR_MASK	(Port->MODER, (uint32_t)0b11 << (Pin*2));
	SET_MASK	(Port->MODER, (uint32_t)Mode << (Pin*2));
}

inline void GPIO_SetOutputType (GPIO_TypeDef* Port, uint8_t Pin, eOutputType_t OutputType)
{
	CLEAR_MASK	(Port->OTYPER, (uint32_t)0b1 << Pin);
	SET_MASK	(Port->OTYPER, (uint32_t)OutputType << Pin);
}

inline void GPIO_SetOutputSpeed (GPIO_TypeDef* Port, uint8_t Pin, eOutputSpeed_t OutputSpeed)
{
	CLEAR_MASK	(Port->OSPEEDR, (uint32_t)0b11 << (Pin*2));
	SET_MASK	(Port->OSPEEDR, (uint32_t)OutputSpeed << (Pin*2));
}

inline void GPIO_SetPullResistor (GPIO_TypeDef* Port, uint8_t Pin, ePullResistor_t PullResistor)
{
	CLEAR_MASK	(Port->PUPDR, (uint32_t)0b11 << (Pin*2));
	SET_MASK	(Port->PUPDR, (uint32_t)PullResistor << (Pin*2));
}

inline void GPIO_SetPin	(GPIO_TypeDef* Port, uint8_t Pin)
{
	SET_MASK(Port->BSRR, (uint32_t)1<<Pin);
}
inline void GPIO_ResetPin (GPIO_TypeDef* Port, uint8_t Pin)
{
	SET_MASK (Port->BSRR, (uint32_t)1<<(Pin+16));
}
inline void GPIO_InvPin (GPIO_TypeDef* Port, uint8_t Pin)
{
	if ( READ_BIT(Port->ODR, (uint32_t)1<<Pin) ) {
		GPIO_ResetPin (Port, Pin);
	} else {
		GPIO_SetPin (Port, Pin);
	}
}

#endif // STM32F4_LLUL_H
/**
 * Библиотека инлайн функций для работы с регистрами
 * llul - low layer user lib
 */
#include "stm32f4_bf.h"

#ifndef STM32F4_LLUL_H
#define STM32F4_LLUL_H

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

typedef enum {
	AHBnotdiv	= 0,
	AHBdiv2		= 0b1000,
	AHBdiv4		= 0b1001,
	AHBdiv8		= 0b1010,
	AHBdiv16	= 0b1011,
	AHBdiv64	= 0b1100,
	AHBdiv128	= 0b1101,
	AHBdiv256	= 0b1110,
	AHBdiv512	= 0b1111
} eAHBprescaler_t;

inline void RCC_SetAHBprescaler (eAHBprescaler_t prescaler)
{
	extern volatile RCC_CFGR_t* RCC_CFGR;
	RCC_CFGR->HPRE = prescaler;
}

typedef enum {
	APBnotdiv	= 0,
	APBdiv2		= 0b100,
	APBdiv4		= 0b101,
	APBdiv8		= 0b110,
	APBdiv16	= 0b111
} eAPBprescaler_t;

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

typedef enum {
	HSI		= 0,
	HSE		= 0b01,
	PLL		= 0b10
} eSystemClockSwitch_t;

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

typedef enum {
	PLLP_div2 = 0b00,
	PLLP_div4 = 0b01,
	PLLP_div6 = 0b10,
	PLLP_div8 = 0b11
} ePLLPdiv_t;

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

typedef enum {
	HSIsource = 0b0,
	HSEsource = 0b1
} ePLLPsource_t;

inline void RCC_SetPLLsource (ePLLPsource_t source)
{
	extern volatile RCC_PLLCFGR_t* RCC_PLLCFGR;
	RCC_PLLCFGR->PLLSRC = source;
}

/*****************************************************************************
 *		FLASH
 ****************************************************************************/
typedef enum {
	latency_0 = 0,
	latency_1,
	latency_2,
	latency_3,
	latency_4,
	latency_5,
	latency_6,
	latency_7
} eLatency_t;
inline void FLASH_SetLatency (eLatency_t Latency)
{
	extern volatile FLASH_ACR_t* FLASH_ACR;
	FLASH_ACR->LATENCY = Latency;
}

#endif // STM32F4_LLUL_H
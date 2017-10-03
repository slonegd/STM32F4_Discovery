/**
 * Библиотека инлайн функций для работы с регистрами
 * llul - low layer user lib
 */
#include "stm32f4_bf.hpp"

#ifndef STM32F4_LLUL_H
#define STM32F4_LLUL_H

#define SET_MASK(REG, MASK)		((REG) |= (MASK))
#define CLEAR_MASK(REG, MASK)	((REG) &= ~(MASK))




/*****************************************************************************
 *		FLASH
 ****************************************************************************/
inline void FLASH_SetLatency (Latency_t Latency)
{
	extern volatile FLASH_ACR_t* FLASH_ACR;
	FLASH_ACR->LATENCY = Latency;
}



#endif // STM32F4_LLUL_H
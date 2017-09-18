/**
 * Файл с заданием адресов регистров в виде битовых полей
 */
#include "stm32f4_bf.hpp"

/*****************************************************************************
 *		RCC
 ****************************************************************************/
volatile RCC_CR_t*		RCC_CR      = (RCC_CR_t*)       (&(RCC->CR));
volatile RCC_PLLCFGR_t* RCC_PLLCFGR = (RCC_PLLCFGR_t*)  (&(RCC->PLLCFGR));
volatile RCC_CFGR_t*    RCC_CFGR 	= (RCC_CFGR_t*)   	(&(RCC->CFGR));
volatile RCC_AHB1ENR_t* RCC_AHB1ENR = (RCC_AHB1ENR_t*)  (&(RCC->AHB1ENR));

/*****************************************************************************
 *		FLASH
 ****************************************************************************/
volatile FLASH_ACR_t*	FLASH_ACR 	= (FLASH_ACR_t*)   	(&(FLASH->ACR));

/*****************************************************************************
 *		GPIO
 ****************************************************************************/
#define MakeModer(c) volatile const GPIO_MODER_t* GPIO##c##_MODER =\
						 (GPIO_MODER_t*) (&(GPIO##c->MODER))
MakeModer (A);
MakeModer (B);
MakeModer (C);
MakeModer (D);
MakeModer (E);
MakeModer (F);
MakeModer (G);
MakeModer (H);
MakeModer (I);

#include "stm32f4_deb.h"

/*****************************************************************************
 *		RCC
 ****************************************************************************/
volatile RCC_CR_t*		RCC_CR      = (RCC_CR_t*)       (&(RCC->CR));
volatile RCC_PLLCFGR_t* RCC_PLLCFGR = (RCC_PLLCFGR_t*)  (&(RCC->PLLCFGR));
volatile RCC_CFGR_t*    RCC_CFGR 	= (RCC_CFGR_t*)   	(&(RCC->CFGR));

/*****************************************************************************
 *		FLASH
 ****************************************************************************/
volatile FLASH_ACR_t*	FLASH_ACR 	= (FLASH_ACR_t*)   	(&(FLASH->ACR));
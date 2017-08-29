#include <stdint.h>
#include "usrlib/stm32f4_deb.h"

volatile uint32_t i = 0;
volatile uint32_t j = 0;
extern volatile RCC_CR_t*		RCC_CR;
extern volatile RCC_PLLCFGR_t*	RCC_PLLCFGR;
extern volatile RCC_CFGR_t*		RCC_CFGR;
extern volatile FLASH_ACR_t*	FLASH_ACR;

int main(void)
{
	FLASH_ACR->LATENCY = 5;
	RCC_CR->HSEON = 1;
	while (RCC_CR->HSERDY != 1) { }
	RCC_CFGR->HPRE = 0;			//not div
	RCC_CFGR->PPRE1 = 0b110;	//div4
	RCC_CFGR->PPRE2 = 0b100;	//div2
	RCC_CFGR->SW = 0b10;	    //PLL
	RCC_PLLCFGR->PLLM = 8;
	RCC_PLLCFGR->PLLN = 168;
	RCC_PLLCFGR->PLLP = 0b01;	//div2
	RCC_PLLCFGR->PLLQ = 4;
	RCC_PLLCFGR->PLLSRC = 1;	//HSE
	RCC_CR->PLLON = 1;
	while (RCC_CR->PLLRDY != 1) { }

	while (1)
	{
		i++;
		j--;
	}
}
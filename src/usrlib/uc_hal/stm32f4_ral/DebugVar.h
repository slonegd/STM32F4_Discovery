#pragma once

#include "RCC_ral.h"
#include "FLASH_ral.h"
#include "GPIO_ral.h"
#include "TIM_ral.h"
#include "USART_ral.h"

volatile RCC_t* RCC_d = (RCC_t*) RCC;
volatile GPIO_t* GPIOA_d = (GPIO_t*) GPIOA;
volatile GPIO_t* GPIOB_d = (GPIO_t*) GPIOB;
volatile GPIO_t* GPIOC_d = (GPIO_t*) GPIOC;
volatile GPIO_t* GPIOD_d = (GPIO_t*) GPIOD;
volatile GPIO_t* GPIOE_d = (GPIO_t*) GPIOE;
volatile GPIO_t* GPIOF_d = (GPIO_t*) GPIOF;
volatile FLASH_t* FLASH_d = (FLASH_t*) FLASH;
volatile TIM_t* TIM2_d = (TIM_t*) TIM2;
volatile TIM_t* TIM3_d = (TIM_t*) TIM3;
volatile TIM_t* TIM4_d = (TIM_t*) TIM4;
volatile USART_t* USART1_d = (USART_t*) USART1;
volatile USART_t* USART2_d = (USART_t*) USART2;
volatile USART_t* USART3_d = (USART_t*) USART3;
volatile USART_t* USART6_d = (USART_t*) USART6;

inline void makeDebugVar (void)
{
    RCC_d->CR_t::bits.dcb1 = 0;
    FLASH_d->ACR_t::bits.dcb1 = 0;
    GPIOA_d->BSRR_t::reg = 0;
    GPIOB_d->BSRR_t::reg = 0;
    GPIOC_d->BSRR_t::reg = 0;
    GPIOD_d->BSRR_t::reg = 0;
    GPIOE_d->BSRR_t::reg = 0;
    GPIOF_d->BSRR_t::reg = 0;
    TIM2_d->CR1_t::bits.dcb = 0;
    TIM3_d->CR1_t::bits.dcb = 0;
    TIM4_d->CR1_t::bits.dcb = 0;
    USART1_d->CR1_t::bits.dcb1 = 0;
    USART2_d->CR1_t::bits.dcb1 = 0;
    USART3_d->CR1_t::bits.dcb1 = 0;
    USART6_d->CR1_t::bits.dcb1 = 0;

}
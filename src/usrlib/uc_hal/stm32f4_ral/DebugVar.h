#pragma once

#include "RCC_ral.h"
#include "GPIO_ral.h"

volatile RCC_t* RCC_d = (RCC_t*) RCC;
volatile GPIO_t* GPIOA_d = (GPIO_t*) GPIOA;
volatile GPIO_t* GPIOB_d = (GPIO_t*) GPIOB;
volatile GPIO_t* GPIOC_d = (GPIO_t*) GPIOC;
volatile GPIO_t* GPIOD_d = (GPIO_t*) GPIOD;
volatile GPIO_t* GPIOE_d = (GPIO_t*) GPIOE;
volatile GPIO_t* GPIOF_d = (GPIO_t*) GPIOF;

inline void makeDebugVar (void)
{
    RCC_d->CR_t::bits.dcb1 = 0;
    GPIOA_d->BSRR_t::reg = 0;
    GPIOB_d->BSRR_t::reg = 0;
    GPIOC_d->BSRR_t::reg = 0;
    GPIOD_d->BSRR_t::reg = 0;
    GPIOE_d->BSRR_t::reg = 0;
    GPIOF_d->BSRR_t::reg = 0;
}
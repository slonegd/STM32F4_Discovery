/**
 * Библиотека классов портов
 * Каждый порт предствлен в виде отдельного статического клсса
 * и может быть передан в качестве параметра шаблона
 */

#include "stm32f4_bf.h"

#ifndef PORTC_HPP
#define PORTC_HPP

#define MAKE_STATIC_CLASS_PORT(LETTER) \
	class P##LETTER \
	{ \
	public:	\
		static volatile GPIO_MODER_t &moder() {	\
			return (GPIO_MODER_t &)GPIO##LETTER->MODER;	\
		} \
		static volatile GPIO_OTYPER_t &otyper() { \
			return (GPIO_OTYPER_t &)GPIO##LETTER->OTYPER; \
		} \
		static volatile GPIO_OSPEEDR_t &ospeedr() { \
			return (GPIO_OSPEEDR_t &)GPIO##LETTER->OSPEEDR; \
		} \
		static volatile GPIO_PUPDR_t &pupdr() { \
			return (GPIO_PUPDR_t &)GPIO##LETTER->PUPDR; \
		} \
		static volatile RCC_AHB1ENR_t &ahb1enr() { \
			return (RCC_AHB1ENR_t &)RCC->AHB1ENR; \
		} \
		static volatile GPIO_ODR_t &odr() { \
			return (GPIO_ODR_t &)GPIO##LETTER->ODR; \
		} \
		static volatile uint32_t &bsrr() { \
			return (uint32_t &)GPIO##LETTER->BSRR; \
		} \
		inline static void ClockEnable (void) \
		{ \
			ahb1enr().GPIO##LETTER##EN = 0b1; \
		} \
	} // class P##LETTER

MAKE_STATIC_CLASS_PORT (A);
MAKE_STATIC_CLASS_PORT (B);
MAKE_STATIC_CLASS_PORT (C);
MAKE_STATIC_CLASS_PORT (D);
MAKE_STATIC_CLASS_PORT (E);
MAKE_STATIC_CLASS_PORT (F);
MAKE_STATIC_CLASS_PORT (G);
MAKE_STATIC_CLASS_PORT (H);
MAKE_STATIC_CLASS_PORT (I);



#endif // PORTC_HPP
#pragma once
#ifndef INIT_H
#define INIT_H

#include <stdint.h>
#include "defines.h"
#include "usrlib/stm32f4_bf.hpp"
#include "usrlib/stm32f4_llul.h"
#include "usrlib/stm32f4_RegClasses.hpp"
#include "usrlib/timer.h"
#include "usrlib/tim2-5.hpp"

inline void CLKinit (void)
{
	FLASH_SetLatency (Latency_t::latency_5);
	RCC_HSEon ();
	RCC_WaitHSEready ();
	RCC_SetAHBprescaler (AHBprescaler_t::notdiv);
	RCC_SetAPB1prescaler(APBprescaler_t::div4);
	RCC_SetAPB2prescaler(APBprescaler_t::div2);
	RCC_SystemClockSwitch (SystemClockSwitch_t::PLL);
	RCC_SetPLLM (8);
	RCC_SetPLLN (168);
// 1 : через статический класс						1596
//	RCC_::SetPLLP (RCC_::PLLPdiv::div2);
// 2 : через объект (еще необходимо проверить)		1596
	RCC_PLLCFGR r;
//	r.bits.PLLP = RCC_PLLCFGR::PLLPdiv::div2;
	r.rSetPLLP (RCC_PLLCFGR::PLLPdiv::div2);
// 3 : функция с внешней глобальной переменной 		1592
//	RCC_SetPLLP (PLLPdiv_t::div2);
// 4 : CMSIS										1596
//	RCC->PLLCFGR &= ~(RCC_PLLCFGR_PLLP_Msk);
//	RCC->PLLCFGR |= RCC_PLLCFGR_PLLP_0;

	RCC_SetPLLQ (4);
	RCC_SetPLLsource (PLLsource_t::HSE);
	RCC_PLLon ();
	RCC_WaitPLLready ();


}

template <class T>
static inline void SetLed (void)
{
    T::SetModer (Mode_t::OutputMode);
    T::SetOutputType (OutputType_t::PushPull);
	T::SetOutputSpeed (OutputSpeed_t::HighSpeed);
	T::SetPullResistor (PullResistor_t::No);
};

inline void PortsInit (void)
{
	LedPort::ClockEnable();

    SetLed <Bled> ();
    SetLed <Rled> ();
    SetLed <Oled> ();
    SetLed <Gled> ();
}

inline void TimeEventInit (void)
{
	TimerSetTimeAndStart (BledTimer, 60);
	TimerSetTimeAndStart (GledTimer, 61);
	TimerSetTimeAndStart (OledTimer, 62);
	TimerSetTimeAndStart (RledTimer, 63);
}

inline void PWMinit (void)
{
	T2::CountEnable ();
}

#endif // INIT_H
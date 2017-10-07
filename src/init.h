#pragma once

#include <stdint.h>
#include "defines.h"
#include "usrlib/stm32f4_bf.hpp"
#include "usrlib/stm32f4_llul.h"
#include "usrlib/tim2-5.hpp"
#include "usrlib/timers.h"


inline void CLKinit (void)
{
	FLASH_SetLatency (Latency_t::latency_5);
    RCC_t::HSEon ();
    RCC_t::waitHSEready ();
    RCC_t::setAHBprescaler (RCC_t::AHBprescaler::AHBnotdiv);
    RCC_t::setAPB1prescaler (RCC_t::APBprescaler::APBdiv4);
    RCC_t::setAPB2prescaler (RCC_t::APBprescaler::APBdiv2);
    RCC_t::systemClockSwitch (RCC_t::SystemClockSwitch::CS_PLL);
    RCC_t::setPLLM (4);
    RCC_t::setPLLN (168);
    RCC_t::setPLLP (RCC_t::PLLPdiv::PLLdiv2);
//  RCC_t::setPLLQ (4);
    RCC_t::setPLLsource (RCC_t::PLLsource::sHSE);
    RCC_t::PLLon ();
    RCC_t::waitPLLready ();
}


inline void PortsInit (void)
{
	LedPort::ClockEnable();

    Bled::Configure (GPIO_t::Mode_t::OutputMode,
                     GPIO_t::OutType_t::PushPull,
                     GPIO_t::OutSpeed_t::High,
                     GPIO_t::PullResistor_t::No);
    Rled::Configure (GPIO_t::Mode_t::OutputMode,
                     GPIO_t::OutType_t::PushPull,
                     GPIO_t::OutSpeed_t::High,
                     GPIO_t::PullResistor_t::No);
    Oled::Configure (GPIO_t::Mode_t::OutputMode,
                     GPIO_t::OutType_t::PushPull,
                     GPIO_t::OutSpeed_t::High,
                     GPIO_t::PullResistor_t::No);
    Gled::Configure (GPIO_t::Mode_t::OutputMode,
                     GPIO_t::OutType_t::PushPull,
                     GPIO_t::OutSpeed_t::High,
                     GPIO_t::PullResistor_t::No);
}

inline void PWMinit (void)
{
	T2::CountEnable ();
}


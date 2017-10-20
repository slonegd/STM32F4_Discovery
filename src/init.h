#pragma once

#include <stdint.h>
#include "defines.h"
#include "timers.h"


inline void CLKinit (void)
{
    FLASH_t::SetLatency (FLASH_t::Latency::latency_5);
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

    Bled::Configure (Bled::Mode::OutputMode,
                     Bled::OutType::PushPull,
                     Bled::OutSpeed::High,
                     Bled::PullResistor::No);
    Oled::Configure (Oled::Mode::OutputMode,
                     Oled::OutType::PushPull,
                     Oled::OutSpeed::High,
                     Oled::PullResistor::No);
    Gled::Configure (Gled::Mode::OutputMode,
                     Gled::OutType::PushPull,
                     Gled::OutSpeed::High,
                     Gled::PullResistor::No);

    Button::Port::ClockEnable();
}




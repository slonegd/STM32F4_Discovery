#pragma once

#include <stdint.h>
#include "defines.h"
#include "timers.h"


// программные таймеры
const uint8_t timersQty = 2;
Timers<timersQty> timers;
auto& ledTimer = timers.all[0];
auto& butTimer = timers.all[1];

// энергонезависимые данные
const uint8_t flashSector = 2;
Flash<FlashData, flashSector> flash;

// шим
PWM<PWMtimer, PWMout> pwm;

// уарт модбаса
const uint8_t bufSize = 30;
using USART_ = USART<USART1_t, bufSize, RXpin, TXpin, RTSpin>;
USART_ uart;

// модбас
using Modbus = MBslave<InRegs, OutRegs, USART_>;
auto modbus = Modbus(uart);

// действия на входные регистры модбаса
#define ADR(reg)    GET_ADR(InRegs, reg)
inline void mbRegInAction ()
{
    switch ( modbus.getInRegAdrForAction() ) {
        case ADR(reg0):
            ; // сделать чтото
            break;
        case ADR(reg1):
            ; // сделать чтото
            break;
        default: ;
    }
}



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




#pragma once

#include <stdint.h>
#include "defines.h"
#include "DebugVar.h"
#include "RCC_ral.h"
#include "pin_hal.h"
#include "flash_hal.h"
#include "pwm_hal.h"
#include "flash_hal.h"
#include "adc_hal.h"
#include "timers.h"
#include "pinlist.h"
#include "modbusSlave.h"


// discoveri 
using LedPort = PD;
using Bled = PD15;
using Rled = PD14;
using Oled = PD13;
using Gled = PD12;
using Leds = PinList<Bled, Oled>;
using Button = PA0;

// программные таймеры
const uint8_t timersQty = 4;
Timers<timersQty> timers;
auto& ledTimer = timers.all[0];
auto& butTimer = timers.all[1];
auto& mbTimer  = timers.all[2];
auto& txTimer  = timers.all[3];

// энергонезависимые данные
struct FlashData {
    uint16_t d1;
    uint16_t d2;
};
const uint8_t flashSector = 2;
Flash<FlashData, flashSector> flash;

// шим
using PWMout = Rled;
using PWMtimer = TIM4_t;
PWM<PWMtimer, PWMout> pwm;

// уарт модбаса
using RXpin = PA3;
using TXpin = PA2;
using RTSpin = PA5;
using LEDpin = Gled;
const uint8_t bufSize = 30;
using USART_ = USART<USART2_t, bufSize, RXpin, TXpin, RTSpin, LEDpin>;
USART_ uart;

// модбас
struct InRegs {
    uint16_t reg0;
    uint16_t reg1;
};
struct OutRegs {
    uint16_t reg0;
    uint16_t reg1;
};
auto modbus = MBslave<InRegs, OutRegs, USART_> (uart, mbTimer);
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
    RCC_t::HSEon();
    RCC_t::waitHSEready();
    RCC_t::setAHBprescaler (RCC_t::AHBprescaler::AHBnotdiv);
    RCC_t::setAPB1prescaler (RCC_t::APBprescaler::APBdiv4);
    RCC_t::setAPB2prescaler (RCC_t::APBprescaler::APBdiv2);
    RCC_t::systemClockSwitch (RCC_t::SystemClockSwitch::CS_PLL);
    RCC_t::setPLLM<4>();
    RCC_t::setPLLN<168>();
    RCC_t::setPLLP (RCC_t::PLLPdiv::PLLdiv2);
//  RCC_t::setPLLQ<4>();
    RCC_t::setPLLsource (RCC_t::PLLsource::sHSE);
    RCC_t::PLLon();
    RCC_t::waitPLLready();
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




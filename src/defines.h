#pragma once

#include "pin_hal.h"
#include "pinlist.h"
#include "flash_hal.h"
#include "TIM_ral.h"
#include "pwm_hal.h"
#include "RCC_ral.h"
#include "FLASH_ral.h"
#include "DebugVar.h"
#include "modbusSlave.h"

#define F_OSC   8000000UL
#define F_CPU   168000000UL

// discoveri leds
using LedPort = PD;
using Bled = PD15;
using Rled = PD14;
using Oled = PD13;
using Gled = PD12;
using Leds = PinList<Bled, Gled, Oled>;

using Button = PA0;

using PWMout = Rled;
using PWMtimer = TIM4_t;

const uint32_t fCPU = 168000000;

// энергонезависимые данные
struct FlashData {
    uint16_t d1;
    uint16_t d2;
};

// модбас
enum class InRegs {
    reg0,
    reg1,
    Qty
};
enum class OutRegs {
    reg0,
    reg1,
    reg2,
    Qty
};
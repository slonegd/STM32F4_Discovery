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
#include "adc_hal.h"

#define F_OSC   8000000UL
#define F_CPU   168000000UL

const uint32_t fCPU = 168000000;

// discoveri leds
using LedPort = PD;
using Bled = PD15;
using Rled = PD14;
using Oled = PD13;
using Gled = PD12;
// pinlist test
using Leds = PinList<Bled, Gled, Oled>;

// discovery button
using Button = PA0;

// led for PWM
using PWMout = Rled;
using PWMtimer = TIM4_t;


// энергонезависимые данные
struct FlashData {
    uint16_t d1;
    uint16_t d2;
};

// uart pin
using RXpin = PA3;
using TXpin = PA2;
using RTSpin = PA5;

// modbus register
struct InRegs {
    uint16_t reg0;
    uint16_t reg1;
};
struct OutRegs {
    uint16_t reg0;
    uint16_t reg1;
};

// adc

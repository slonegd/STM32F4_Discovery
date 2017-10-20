#pragma once

#include "pin_hal.h"
#include "pinlist.h"
#include "TIM_ral.h"
#include "pwm_hal.h"
#include "RCC_ral.h"
#include "FLASH_ral.h"
#include "DebugVar.h"

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
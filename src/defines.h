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
using Bled = Pin_t<PD,15>;
using Rled = Pin_t<PD,14>;
using Oled = Pin_t<PD,13>;
using Gled = Pin_t<PD,12>;

using Leds = PinList<Bled, Gled, Oled, Rled>;

using PWMout = Pin_t<PA,1>;
using PWMtimer = TIM2_t;
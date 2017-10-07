#pragma once

#include "usrlib/uc_hal/pin_hal.h"
#include "usrlib/uc_hal/stm32f4_ral/RCC_ral.h"
#include "usrlib/uc_hal/stm32f4_ral/DebugVar.h"


#define F_CPU   168000000UL

// discoveri leds
typedef PD LedPort;
typedef Pin_t<PD,15> Bled;
typedef Pin_t<PD,14> Rled;
typedef Pin_t<PD,13> Oled;
typedef Pin_t<PD,12> Gled;
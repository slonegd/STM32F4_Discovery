#include <stdint.h>
#include "defines.h"
#include "usrlib/stm32f4_bf.h"
#include "usrlib/stm32f4_llul.h"
#include "usrlib/timer.h"

#ifndef INIT_H
#define INIT_H

inline void CLKinit (void)
{
	FLASH_SetLatency (latency_5);
	RCC_HSEon ();
	RCC_WaitHSEready ();
	RCC_SetAHBprescaler (AHBnotdiv);
	RCC_SetAPB1prescaler(APBdiv4);
	RCC_SetAPB2prescaler(APBdiv2);
	RCC_SystemClockSwitch (PLL);
	RCC_SetPLLM (8);
	RCC_SetPLLN (168);
	RCC_SetPLLP (PLLP_div2);
	RCC_SetPLLQ (4);
	RCC_SetPLLsource (HSEsource);
	RCC_PLLon ();
	RCC_WaitPLLready ();
}

inline void PortsInit (void)
{
	LedPort::ClockEnable();

	Bled::SetModer (OutputMode);
	Bled::SetOutputType (PushPull);
	Bled::SetOutputSpeed (HighSpeed);
	Bled::SetPullResistor (NoResistor);

	Rled::SetModer (OutputMode);
	Rled::SetOutputType (PushPull);
	Rled::SetOutputSpeed (HighSpeed);
	Rled::SetPullResistor (NoResistor);

	Oled::SetModer (OutputMode);
	Oled::SetOutputType (PushPull);
	Oled::SetOutputSpeed (HighSpeed);
	Oled::SetPullResistor (NoResistor);

	Gled::SetModer (OutputMode);
	Gled::SetOutputType (PushPull);
	Gled::SetOutputSpeed (HighSpeed);
	Gled::SetPullResistor (NoResistor);
}


inline void TimeEventInit (void)
{
	TimerSetTimeAndStart (BledTimer, 110);
	TimerSetTimeAndStart (GledTimer, 120);
	TimerSetTimeAndStart (OledTimer, 130);
	TimerSetTimeAndStart (RledTimer, 140);
}

#endif // INIT_H
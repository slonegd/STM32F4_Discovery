#include <stdint.h>
#include "usrlib/stm32f4_bf.h"
#include "usrlib/stm32f4_llul.h"
#include "usrlib/timer.h"
//#include "usrlib/ports.hpp"

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
//	extern volatile GPIO_MODER_t*	GPIOA_MODER;
	RCC_PortClockEnable (LED_PORT);

	GPIO_SetModer		(LED_PORT, BLED_PIN, OutputMode);
	GPIO_SetOutputType	(LED_PORT, BLED_PIN, PushPull);
	GPIO_SetOutputSpeed (LED_PORT, BLED_PIN, HighSpeed);
	GPIO_SetPullResistor (LED_PORT, BLED_PIN, NoResistor);

	GPIO_SetModer		(LED_PORT, RLED_PIN, OutputMode);
	GPIO_SetOutputType	(LED_PORT, RLED_PIN, PushPull);
	GPIO_SetOutputSpeed (LED_PORT, RLED_PIN, HighSpeed);
	GPIO_SetPullResistor (LED_PORT, RLED_PIN, NoResistor);	

	GPIO_SetModer		(LED_PORT, OLED_PIN, OutputMode);
	GPIO_SetOutputType	(LED_PORT, OLED_PIN, PushPull);
	GPIO_SetOutputSpeed (LED_PORT, OLED_PIN, HighSpeed);
	GPIO_SetPullResistor (LED_PORT, OLED_PIN, NoResistor);

	GPIO_SetModer		(LED_PORT, GLED_PIN, OutputMode);
	GPIO_SetOutputType	(LED_PORT, GLED_PIN, PushPull);
	GPIO_SetOutputSpeed (LED_PORT, GLED_PIN, HighSpeed);
	GPIO_SetPullResistor (LED_PORT, GLED_PIN, NoResistor);
//	GPIOA_MODER->MODER1 = 0b01;
//	PA::SetModer (OutputMode);
}


inline void TimeEventInit (void)
{
	TimerSetTime (BledTimer, 100);
	TimerSetTime (GledTimer, 150);
	TimerSetTime (OledTimer, 200);
	TimerSetTime (RledTimer, 250);
	TimerStart (BledTimer);
	TimerStart (GledTimer);
	TimerStart (OledTimer);
	TimerStart (RledTimer);
}

#endif // INIT_H
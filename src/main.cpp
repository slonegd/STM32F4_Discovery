#include "init.h"

#include "pinlist.h"

using Leds = MakePinList<0, Bled, Gled, Oled, Rled>::Result;
using LedsPort = Bled::Port;
//using PortsList =  PinListProperties<Leds>::PinsToPorts;
using LedsPorts = PinListProperties<Leds>::Ports;
volatile uint8_t l = PinListProperties<Leds>::Length;
volatile uint8_t k = Loki::TL::Length<LedsPorts>::value;
volatile uint32_t j = GetPortMask<Leds>::value;




Timers<4> timers;
auto& bLedTimer = timers.all[0];
auto& gLedTimer = timers.all[1];
auto& oLedTimer = timers.all[2];
auto& rLedTimer = timers.all[3];

int main(void)
{
    makeDebugVar();
    
    // инициализация системных частот
    CLKinit ();
    PortsInit ();
    // инициализация аппаратного таймера 1мс
    timers.msHardvareInit();
    // инициализация таймера с шим
    PWMinit ();
    // инициализация программных таймеров задач
    bLedTimer.setTimeAndStart (l);
    gLedTimer.setTimeAndStart (k);
    oLedTimer.setTimeAndStart (j);
    rLedTimer.setTimeAndStart (170);

	while (1)
	{
        timers.update();

        if ( bLedTimer.event() ) {
            Bled::Invert();
        }

        if ( gLedTimer.event() ) {
            Gled::Invert();
        }

        if ( oLedTimer.event() ) {
            Oled::Invert();
        }

        if ( rLedTimer.event() ) {
            Rled::Invert();
        }
    } // while (1)
}


/*****************************************************************************
*
*       ПРЕРЫВАНИЯ
*
*****************************************************************************/
extern "C" void SysTick_Handler (void)
{
    timers.tick();
}
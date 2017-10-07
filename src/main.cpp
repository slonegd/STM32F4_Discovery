#include "init.h"

Timers bLedTimer;
Timers gLedTimer;
Timers oLedTimer;
Timers rLedTimer;

int main(void)
{
    // инициализация системных частот
    CLKinit ();
    PortsInit ();
    // инициализация аппаратного таймера 1мс
    Timers::msHardvareInit();
    // инициализация таймера с шим
    PWMinit ();
    // инициализация программных таймеров задач
    bLedTimer.setTimeAndStart (500);
    gLedTimer.setTimeAndStart (61);
    oLedTimer.setTimeAndStart (62);
    rLedTimer.setTimeAndStart (63);

	while (1)
	{
        Timers::update();

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
    Timers::tick();
}
#include "init.h"

Timers<4> timers;
Timer& bLedTimer = timers.all[0];
Timer& gLedTimer = timers.all[1];
Timer& oLedTimer = timers.all[2];
Timer& rLedTimer = timers.all[3];

int main(void)
{
    // инициализация системных частот
    CLKinit ();
    PortsInit ();
    // инициализация аппаратного таймера 1мс
    timers.msHardvareInit();
    // инициализация таймера с шим
    PWMinit ();
    // инициализация программных таймеров задач
    bLedTimer.setTimeAndStart (500);
    gLedTimer.setTimeAndStart (100);
    oLedTimer.setTimeAndStart (150);
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
#include "init.h"

uint16_t i = 0;

Timers<1> timers;
auto& ledTimer = timers.all[0];


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
    ledTimer.setTimeAndStart (100);
   

	while (1)
	{
        timers.update();

        if ( ledTimer.event() ) {
            Leds::Write(i++);
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
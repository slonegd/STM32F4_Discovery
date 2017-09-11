#include "init.h"

volatile uint32_t ii = 0;
volatile uint32_t jj = 0;

int main(void)
{
    // инициализация системных частот
    CLKinit ();
    PortsInit ();
    // инициализация аппаратного таймера 1мс
    TimerInit ();
    // инициализация таймера с шим
    PWMinit ();
	// инициализация программных таймеров задач
    TimeEventInit ();

	while (1)
	{
        TimersUpdate ();

        if ( TimerEvent (BledTimer) ) {
            ii++;
            Bled::Invert();
        }
        if ( TimerEvent (GledTimer) ) {
            jj++;
            Gled::Invert();
        }
        if ( TimerEvent (OledTimer) ) {
            Oled::Invert();
        }
        if ( TimerEvent (RledTimer) ) {
            Rled::Invert();
        }
    }
}


/*****************************************************************************
*
*       ПРЕРЫВАНИЯ
*
*****************************************************************************/
extern "C" void SysTick_Handler (void)
{
    TimerInc();
}
#include "init.h"

uint16_t i = 0;

PWM<PWMtimer, PWMout> pwm;

Timers<1> timers;
auto& ledTimer = timers.all[0];


int main(void)
{
    makeDebugVar();
    
    // инициализация системных частот
    CLKinit ();
    PortsInit ();

    // инициализация таймера с шим

    // инициализация программных таймеров задач
    ledTimer.setTimeAndStart (500);
   

	while (1)
	{
        timers.update();

        if ( ledTimer.event() ) {
            Leds::Write(i++);
            pwm.stop();
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
#include "init.h"

uint16_t i = 0;
volatile uint8_t j = 0;
bool goUp = true;

PWM<PWMtimer, PWMout> pwm;

Timers<2> timers;
auto& ledTimer = timers.all[0];
auto& pwmTimer = timers.all[1];


int main(void)
{
    makeDebugVar();
    
    // инициализация системных частот
    CLKinit ();
    PortsInit ();

    // инициализация таймера с шим
    PWMtimer::SetARR (0x00FF);
    pwm.start();

    // инициализация программных таймеров задач
    ledTimer.setTimeAndStart (500);
    pwmTimer.setTimeAndStart (10);
   

	while (1)
	{
        timers.update();

        if ( ledTimer.event() ) {
            Leds::Write(i++);
        }

        if ( pwmTimer.event() ) {
            goUp ? j++ : j--;
            goUp =  (j == 255) ? false :
                    (j == 0)   ? true  :
                                 goUp;
            PWMtimer::SetCCR3 (j);
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
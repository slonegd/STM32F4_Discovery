#include "init.h"

uint16_t i = 0;

Timers<2> timers;
auto& ledTimer = timers.all[0];
auto& butTimer = timers.all[1];

PWM<PWMtimer, PWMout> pwm;

int main(void)
{
    makeDebugVar();
   
    // инициализация системных частот
    CLKinit ();
    PortsInit ();

    // инициализация таймера с шим
    // прескаллер спецом, чтбы было видно на индикаторе высокие частоты
    PWMtimer::SetPrescaller (10000);
    pwm.setFreq (10000);
    pwm.setD (50);

    // инициализация программных таймеров задач
    ledTimer.setTimeAndStart (500);
    butTimer.setTimeAndStart (200);
   

	while (1)
	{
        timers.update();

        if ( ledTimer.event() ) {
            Leds::Write(i++);
        }

        if ( butTimer.event() ) {
            bool butActDone = false;
            static bool goUp = true;
            static uint8_t d = 50;

            if ( !Button::IsSet() ) {
                butActDone = false;
            } else if ( !butActDone ) {
                butActDone = true;

                d = goUp ? d+10 : d-10;
                goUp = (d == 100) ? false :
                       (d == 0)   ? true  :
                                    goUp;
                pwm.setD (d);

                if ( pwm.isOutEnable() ) {
                    pwm.outDisable();
                } else {
                    pwm.outEnable();
                }
            }
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
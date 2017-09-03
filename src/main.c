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
	// инициализация программных таймеров задач
    TimeEventInit ();

	while (1)
	{
        TimersUpdate ();

        if ( TimerEvent (BledTimer) ) {
            ii++;
            GPIO_InvPin (LED_PORT, BLED_PIN);
        }
        if ( TimerEvent (GledTimer) ) {
            jj++;
            GPIO_InvPin (LED_PORT, GLED_PIN);
        }
        if ( TimerEvent (OledTimer) ) {
            GPIO_InvPin (LED_PORT, OLED_PIN);
        }
        if ( TimerEvent (RledTimer) ) {
             GPIO_InvPin (LED_PORT, RLED_PIN);
        }
		
	}
}


/****************************************************************************
 * 
 * прерывания
 * 
 ***************************************************************************/


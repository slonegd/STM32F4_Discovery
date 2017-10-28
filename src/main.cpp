#include "init.h"
#include "USART_hal.h"

uint16_t i = 0;

const uint8_t timersQty = 2;
Timers<timersQty> timers;
auto& ledTimer = timers.all[0];
auto& butTimer = timers.all[1];

const uint8_t flashSector = 2;
Flash<FlashData, flashSector> flash;

PWM<PWMtimer, PWMout> pwm;

const uint8_t bufSize = 30;
using USART_ = USART<USART1_t,bufSize>;
USART_ uart;
// using USART_ = USART<USART1_t,bufSize>;
// USART_::Settings set {USART_::Boudrate::BR9600, false};
// auto uart = USART_ (set);

int main(void)
{
    makeDebugVar();
    USART1_t::SetBoudRate<USART1_t::Boudrate::BR9600, fCPU>();
   
    // инициализация системных частот
    CLKinit ();
    PortsInit ();

    // eeprom
    if ( !flash.readFromFlash() ) {
        flash.data.d1 = 1;
        flash.data.d2 = 3;
    }

    // модбас
    USART_::Settings set = {
        USART_::Boudrate::BR9600,
        USART_::ParityEn::disable,
        USART_::Parity::even,
        USART_::StopBits::_1
    };
    uart.init (set);

    // инициализация таймера с шим
    // прескаллер спецом, чтбы было видно на индикаторе высокие частоты
    PWMtimer::SetPrescaller (1000);
    pwm.setFreq (20000);
    pwm.setD (50);
    pwm.outEnable();

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
            flash.update();
            static bool butActDone = false;
            if ( !Button::IsSet() ) {
                butActDone = false;
            } else if ( !butActDone ) {
                butActDone = true;

                static bool goUp = true;
                static uint8_t d = 50;
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

                flash.data.d2++;
            }
        }

    } // while (1)
}


//////////////////////////////////////////////////////////////////////////////
//       ПРЕРЫВАНИЯ
//////////////////////////////////////////////////////////////////////////////
extern "C" void SysTick_Handler (void)
{
    timers.tick();
}
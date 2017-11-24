#include "init.h"

uint8_t i = 0;

int main(void)
{
    makeDebugVar();
   
    // инициализация системных частот
    CLKinit ();
    PortsInit ();

    // энергонезависимые данные
    if ( !flash.readFromFlash() ) {
        flash.data.d1 = 1;
        flash.data.d2 = 3;
    }

    // модбас, инициализация уарт
    USART_::Settings set = {
        USART_::Boudrate::BR9600,
        USART_::ParityEn::disable,
        USART_::Parity::even,
        USART_::StopBits::_1
    };
    modbus.uart.init (set);

    // инициализация таймера с шим
    // прескаллер спецом, чтбы было видно на индикаторе высокие частоты
    PWMtimer::SetPrescaller (1000);
    pwm.setFreq (20000);
    pwm.setD (50);
    pwm.outEnable();

    // adc
    ADC1_t::ClockEnable();
    ADCaverage<ADC1_t, 16, PC0, DMA1stream0> current;

    // инициализация программных таймеров задач
    ledTimer.setTimeAndStart (500);
    butTimer.setTimeAndStart (200);
    txTimer.setTimeAndStart  (1000);

    //для отладки
    modbus.uart.disableRx();  

   
    while (1)
    {
        timers.update();

        if ( modbus.incomingMessage() ) {
            modbus.handler();
            modbus.foreachRegForActions (mbRegInAction);
        }

        if ( txTimer.event() ) {
//            modbus.uart.disableRx();
            modbus.uart.buffer[0] = 1;
            modbus.uart.buffer[1] = 2;
            modbus.uart.buffer[3] = 3;
            modbus.uart.startTX (7);
            //modbus.uart.sendByte (i);
        }


        if ( ledTimer.event() )
            Leds::Write(i++);

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

                if ( pwm.isOutEnable() )
                    pwm.outDisable();
                else 
                    pwm.outEnable();

                flash.data.d2++;
            }
        }

    } // while (1)
}


//////////////////////////////////////////////////////////////////////////////
//       ПРЕРЫВАНИЯ
//////////////////////////////////////////////////////////////////////////////
extern "C" void SysTick_Handler()
{
    timers.tick();
}

extern "C" void USART1_IRQHandler()
{
    modbus.idleHandler();
}

extern "C" void DMA1_Stream6_IRQHandler()
{
    modbus.uart.txCompleteHandler();
}
#include "init.h"

uint16_t i = 0;

// программные таймеры
const uint8_t timersQty = 2;
Timers<timersQty> timers;
auto& ledTimer = timers.all[0];
auto& butTimer = timers.all[1];

// энергонезависимые данные
const uint8_t flashSector = 2;
Flash<FlashData, flashSector> flash;

// шим
PWM<PWMtimer, PWMout> pwm;

// уарт модбаса
const uint8_t bufSize = 30;
using USART_ = USART<USART1_t, 30, PA3, PA2, PA5>;
USART_ uart;

struct InReg {
    uint16_t reg0;
    uint16_t reg1;
};
struct OutReg {
    uint16_t reg0;
    uint16_t reg1;
};
using Modbusst = stMBslave<InReg>;
Modbusst modbusst;



template<> inline void mbRegInActionst<GET_ADR(InReg, reg0)>()
{
    modbusst.i = 0;
}

// модбас
using Modbus = MBslave<InRegs, OutRegs, USART_>;
auto modbus = Modbus(uart);

// действия на входные регистры модбаса
inline void mbRegInAction ()
{
    switch ( modbus.getInRegForAction() ) {
        case InRegs::reg0:
            ;
            break;
        case InRegs::reg1:
            ;
            break;
        default: ;
    }
}

int main(void)
{
    makeDebugVar();
   
    // инициализация системных частот
    CLKinit ();
    PortsInit ();

    // eeprom
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

    // инициализация программных таймеров задач
    ledTimer.setTimeAndStart (500);
    butTimer.setTimeAndStart (200);

   
    while (1)
    {
        timers.update();

        if ( modbus.uart.rxComplete() ) {
            modbus.handler();
            // действия на изменения входящих регистров
            modbus.foreachRegInActions (mbRegInAction);
            modbusst.foreachRegInActions (mbRegInActionst<1>);
        }

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
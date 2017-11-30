/*****************************************************************************
 * ��� ����, ����� �������� ���������� � char ���� ���� ������ ����
 * � ��������� cp1251
 *////////////////////////////////////////////////////////////////////////////
#include "init.h"
#include <something.h>

uint8_t i = 0;

int main(void)
{
    // � ����� ������� ��� ������� CLKinit (������������� ��������� ������)
    // � ������������ ���������� �������� �� ����� init.h
    makeDebugVar();

    PortsInit ();

    modbus.uart.init ( {
        USART_::Boudrate::BR9600,
        USART_::ParityEn::disable,
        USART_::Parity::even,
        USART_::StopBits::_1
    } );

    // ������ � ���
    // ���������� ������, ���� ���� ����� �� ���������� ������� �������
    PWMtimer::SetPrescaller (1000);
    pwm.setFreq (20000);
    pwm.setD (50);
    pwm.outEnable();

    // adc
    ADC1_t::ClockEnable();
    ADCaverage<ADC1_t, 16, PC0, DMA1stream0> current;

    // ������������� ����������� �������� �����
    ledTimer.setTimeAndStart (500);
    butTimer.setTimeAndStart (200);
    txTimer.setTimeAndStart  (100);

    //��� �������
    modbus.uart.disableRx();

    char string[] = "��";
    string[1] = 'i';
    LCD.setLine(string, 0);
    LCD.setLine("����", 1);

   
    while (1)
    {
        timers.update();

        if ( modbus.incomingMessage() ) {
            modbus.handler();
            modbus.foreachRegForActions (mbRegInAction);
        }

        if ( txTimer.event() ) {
            modbus.uart.buffer[0] = LCD_::DataPins::BSRvalue<0b0101>();
            modbus.uart.buffer[1] = LCD_::DataPins::BSRvalue<0b0101>() >> 8;
            modbus.uart.buffer[2] = LCD_::DataPins::BSRvalue<0b0101>() >> 16;
            modbus.uart.buffer[3] = LCD_::DataPins::BSRvalue<0b0101>() >> 24;
            modbus.uart.buffer[4] = string[0];
            modbus.uart.buffer[5] = string[1];
            modbus.uart.buffer[6] = string[2];
            modbus.uart.buffer[7] = size(string);
            modbus.uart.buffer[8] = StaticAssertTypeEq<PA2,TXpin>();
            modbus.uart.buffer[9] = i;
            modbus.uart.startTX(15);

            LCD.setLine("0123456789abcdef",0);
            LCD.setLine("f0123456789abcd",1);
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
//       ����������
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
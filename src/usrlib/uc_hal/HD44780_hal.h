/*****************************************************************************
 * ��� ����, ����� �������� ���������� � char ���� ���� ������ ����
 * � ��������� cp1251
 * 
 *      HD44780 ����������� dma
 * 
 *      D4-D7 ������ ���� �� ����� ����� (� ����� �������)
 *      
 *      ��������� ��������
 *          � ������ ������ ���� �������� ��������� ���� 
 *          ��� �� ��������� ���� ����� - ��������� ������
 *          ���� �� ����� �������� � ��� dma
 *          
 *          dma ������ ���������� �� ���� ����� (������� ����� ����)
 * 
 *          ��������� ��� ������������� �� �������, �� ����� �� �������
 *          �� ��� ����������� ����� E.
 * 
 * 
 *////////////////////////////////////////////////////////////////////////////

#pragma once

#include <string>
#include "TIM_ral.h"
#include "pin_hal.h"
#include "pinlist.h"
#include "constDef.h"

namespace HD44780_HAL {
    using Channels = DMA_ral::CR_t::Channels;
    using ChannelDef = ConstDef<Channels>;    

    //template<class TIM_, class DMA_, class Pin_> constexpr ChannelDef Channel() { return {Channels::_0, false}; }

    //template<> constexpr ChannelDef Channel<TIM1_t,1>()  { return {1, true}; }

}


template <class RS,
          class RW,
          class E, 
          class D4,
          class D5,
          class D6,
          class D7,
          class TIM_,
          class DMAstream_
> class HD44780
{
public:

    HD44780()
    {
        init();
    }


    // ������������� string � ������ LineN LCD
    // ���� ������ string ������ ������� ������ LCD
    // ��������� �� ����� ���������
    template <uint8_t n>
    void setLine (const char ( &string )[n], uint8_t LineN)
    {
        setLineForDMA (string, n - 1, LineN);
    }


    // ����� ��������� � ������
    using DataPins = PinList<D4,D5,D6,D7>;


private:
    // ���������� �������� LCD
    static const uint8_t CharQty = 80;
    uint32_t data [CharQty*2];
    uint32_t* pData;
    //PWM<TIM_,E> pwm;


    // ��������� ������ ��� dma �� 1 ������ 
    // �� ���� ������� (code) � ������� �� LCD
    template<char code> inline void setCharForDMA()
    {
        *pData     = DataPins::template BSRvalue<(code >> 4) & 0xF>();
        *(pData+1) = DataPins::template BSRvalue<code & 0xF>();      
    }


    // ��������� ������ ��� dma �� ������ �� size, ����� size ������� ��
    // ����� ������
    void setLineForDMA (const char* string, uint8_t size, uint8_t LineN)
    __attribute__((noinline))
    {
        pData = (LineN == 0) ? data : data + CharQty;
        for (uint8_t i = 0; i < size; ++i) {
            switch ( string[i] ) {
                // �����
                case '0': setCharForDMA<0x30>(); break;
                case '1': setCharForDMA<0x31>(); break;
                case '2': setCharForDMA<0x32>(); break;
                case '3': setCharForDMA<0x33>(); break;
                case '4': setCharForDMA<0x34>(); break;
                case '5': setCharForDMA<0x35>(); break;
                case '6': setCharForDMA<0x36>(); break;
                case '7': setCharForDMA<0x37>(); break;
                case '8': setCharForDMA<0x38>(); break;
                case '9': setCharForDMA<0x39>(); break;

                // �����
                case ' ': setCharForDMA<0x20>(); break;
                case '=': setCharForDMA<0x3D>(); break;

                // ��������
                case 'A': setCharForDMA<0x41>(); break;
                case 'B': setCharForDMA<0x42>(); break;
                case 'C': setCharForDMA<0x43>(); break;
                case 'D': setCharForDMA<0x44>(); break;
                case 'E': setCharForDMA<0x45>(); break;
                case 'F': setCharForDMA<0x46>(); break;
                case 'G': setCharForDMA<0x47>(); break;
                case 'H': setCharForDMA<0x48>(); break;
                case 'I': setCharForDMA<0x49>(); break;
                case 'J': setCharForDMA<0x4A>(); break;
                case 'K': setCharForDMA<0x4B>(); break;
                case 'L': setCharForDMA<0x4C>(); break;
                case 'M': setCharForDMA<0x4D>(); break;
                case 'N': setCharForDMA<0x4E>(); break;
                case 'O': setCharForDMA<0x4F>(); break;
                case 'P': setCharForDMA<0x50>(); break;
                case 'Q': setCharForDMA<0x51>(); break;
                case 'R': setCharForDMA<0x52>(); break;
                case 'S': setCharForDMA<0x53>(); break;
                case 'T': setCharForDMA<0x54>(); break;
                case 'U': setCharForDMA<0x55>(); break;
                case 'V': setCharForDMA<0x56>(); break;
                case 'W': setCharForDMA<0x57>(); break;
                case 'X': setCharForDMA<0x58>(); break;
                case 'Y': setCharForDMA<0x59>(); break;
                case 'Z': setCharForDMA<0x5A>(); break;

                case 'a': setCharForDMA<0x61>(); break;
                case 'b': setCharForDMA<0x62>(); break;
                case 'c': setCharForDMA<0x63>(); break;
                case 'd': setCharForDMA<0x64>(); break;
                case 'e': setCharForDMA<0x65>(); break;
                case 'f': setCharForDMA<0x66>(); break;
                case 'g': setCharForDMA<0x67>(); break;
                case 'h': setCharForDMA<0x68>(); break;
                case 'i': setCharForDMA<0x69>(); break;
                case 'j': setCharForDMA<0x6A>(); break;
                case 'k': setCharForDMA<0x6B>(); break;
                case 'l': setCharForDMA<0x6C>(); break;
                case 'm': setCharForDMA<0x6D>(); break;
                case 'n': setCharForDMA<0x6E>(); break;
                case 'o': setCharForDMA<0x6F>(); break;
                case 'p': setCharForDMA<0x70>(); break;
                case 'q': setCharForDMA<0x71>(); break;
                case 'r': setCharForDMA<0x72>(); break;
                case 's': setCharForDMA<0x73>(); break;
                case 't': setCharForDMA<0x74>(); break;
                case 'u': setCharForDMA<0x75>(); break;
                case 'v': setCharForDMA<0x76>(); break;
                case 'w': setCharForDMA<0x77>(); break;
                case 'x': setCharForDMA<0x78>(); break;
                case 'y': setCharForDMA<0x79>(); break;
                case 'z': setCharForDMA<0x7A>(); break;  

                //��������             
                case '�': setCharForDMA<0x41>(); break;
                case '�': setCharForDMA<0xA0>(); break;
                case '�': setCharForDMA<0x42>(); break;
                case '�': setCharForDMA<0xA1>(); break;
                case '�': setCharForDMA<0xE0>(); break;
                case '�': setCharForDMA<0x45>(); break;
                case '�': setCharForDMA<0xA2>(); break;
                case '�': setCharForDMA<0xA3>(); break;
                case '�': setCharForDMA<0xA4>(); break;
                case '�': setCharForDMA<0xA5>(); break;
                case '�': setCharForDMA<0xA6>(); break;
                case '�': setCharForDMA<0x4B>(); break;
                case '�': setCharForDMA<0xA7>(); break;
                case '�': setCharForDMA<0x4D>(); break;
                case '�': setCharForDMA<0x48>(); break;
                case '�': setCharForDMA<0x4F>(); break;
                case '�': setCharForDMA<0xA8>(); break;
                case '�': setCharForDMA<0x50>(); break;
                case '�': setCharForDMA<0x43>(); break;
                case '�': setCharForDMA<0x54>(); break;
                case '�': setCharForDMA<0xA9>(); break;
                case '�': setCharForDMA<0xAA>(); break;
                case '�': setCharForDMA<0x58>(); break;
                case '�': setCharForDMA<0xE1>(); break;
                case '�': setCharForDMA<0xAB>(); break;
                case '�': setCharForDMA<0xAC>(); break;
                case '�': setCharForDMA<0xE2>(); break;
                case '�': setCharForDMA<0xAD>(); break;
                case '�': setCharForDMA<0xAE>(); break;
                case '�': setCharForDMA<0x08>(); break;
                case '�': setCharForDMA<0xAF>(); break;
                case '�': setCharForDMA<0xB0>(); break;
                case '�': setCharForDMA<0xB1>(); break;

                case '�': setCharForDMA<0x61>(); break;
                case '�': setCharForDMA<0xB2>(); break;
                case '�': setCharForDMA<0xB3>(); break;
                case '�': setCharForDMA<0xB4>(); break;
                case '�': setCharForDMA<0xE3>(); break;
                case '�': setCharForDMA<0x65>(); break;
                case '�': setCharForDMA<0xB5>(); break;
                case '�': setCharForDMA<0xB6>(); break;
                case '�': setCharForDMA<0xB7>(); break;
                case '�': setCharForDMA<0xB8>(); break;
                case '�': setCharForDMA<0xB9>(); break;
                case '�': setCharForDMA<0xBA>(); break;
                case '�': setCharForDMA<0xBB>(); break;
                case '�': setCharForDMA<0xBC>(); break;
                case '�': setCharForDMA<0xBD>(); break;
                case '�': setCharForDMA<0x6F>(); break;
                case '�': setCharForDMA<0xBE>(); break;
                case '�': setCharForDMA<0x70>(); break;
                case '�': setCharForDMA<0x63>(); break;
                case '�': setCharForDMA<0xBF>(); break;
                case '�': setCharForDMA<0x79>(); break;
                case '�': setCharForDMA<0xE4>(); break;
                case '�': setCharForDMA<0x78>(); break;
                case '�': setCharForDMA<0xE5>(); break;
                case '�': setCharForDMA<0xC0>(); break;
                case '�': setCharForDMA<0xC1>(); break;
                case '�': setCharForDMA<0xE6>(); break;
                case '�': setCharForDMA<0xC2>(); break;
                case '�': setCharForDMA<0xC3>(); break;
                case '�': setCharForDMA<0xC4>(); break;
                case '�': setCharForDMA<0xC5>(); break;
                case '�': setCharForDMA<0xC6>(); break;
                case '�': setCharForDMA<0xC7>(); break;               

                default: setCharForDMA<0x20>(); break; // ������

            }
            pData = pData + 2;
        } // for
        for (uint8_t i = size; i < 16; ++i) {
            setCharForDMA<0x20>(); // ������
            pData = pData + 2;
        }
    }


    void init()
    {
        RS::Port::ClockEnable();
        RS::Configure ( RS::Mode::OutputMode,
                        RS::OutType::PushPull,
                        RS::OutSpeed::Low,
                        RS::PullResistor::No
        );
        RW::Port::ClockEnable();
        RW::Configure ( RW::Mode::OutputMode,
                        RW::OutType::PushPull,
                        RW::OutSpeed::Low,
                        RW::PullResistor::No
        );
        D4::Port::ClockEnable();
        D4::Configure ( D4::Mode::OutputMode,
                        D4::OutType::PushPull,
                        D4::OutSpeed::Low,
                        D4::PullResistor::No
        );
        D5::Configure ( D5::Mode::OutputMode,
                        D5::OutType::PushPull,
                        D5::OutSpeed::Low,
                        D5::PullResistor::No
        );
        D6::Configure ( D6::Mode::OutputMode,
                        D6::OutType::PushPull,
                        D6::OutSpeed::Low,
                        D6::PullResistor::No
        );
        D7::Configure ( D7::Mode::OutputMode,
                        D7::OutType::PushPull,
                        D7::OutSpeed::Low,
                        D7::PullResistor::No
        );

        // ������
        //pwm.setFreq(100000);
        //pwm.setD(50);
    }
    
};
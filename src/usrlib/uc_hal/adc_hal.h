/** Что хочу
 *      В идеале только инициализацию, а далее просто брать значения
 *      из какой-нибудь структуры.
 * 
 *      Каналов несколько, думаю с помощью ДМА можно их сортировать в
 *      массиве.
 *      Думаю метод гет может считать их сумму канала и выдавать данные
 *      в иделе красиво, но не уверен, что ДМА так сможет.
 *      или сделать прерывание по концу ДМА и произвести сумму, кинуть
 *      в выходной массив или структуру. ДМА можно запустить по таймеру
 *      или сразу, надо еще подумать
 * 
 *      Ещё неплохо было бы хранить массив с историей, чтобы анализировать
 *      форму сигнала
 * 
 *      IL300 для измерения высоких напряжений
 * 
 *  Чтото всё это сложно, делаю проще
 *      есть несколько сигналов, которые надо измерить.
 *      Дма просто циклично пихает значения в буфер
 *      при запросе сигналы складываються из буфера
 *      на каждый сигнал свой дма
 *      количество объектов по количеству сигналов, их ничего не связывает
 * 
 *  в дма2 есть потоки от каждого из адц (по 2)
 *  
 * 
 *////////////////////////////////////////////////////////////////////////////

#pragma once

#include "ADC_ral.h"
#include "DMA_ral.h"

using Channels = DMA_ral::CR_t::Channels;

template<class ADC_, class DMA_> static const Channels channel();
template<class ADC_, class PIN> static const uint8_t adcIn();

template<class ADC_, uint16_t bufSize, class PIN, class DMA_>
class ADCaverage : ADC_
{
public:
    inline void Enable() {}
    inline void Disable() {}
    inline uint32_t get()
    {
        uint32_t sum = 0;
        for (uint16_t i = 0; i < bufSize; i++) {
            sum += buf[i];
        }
        return sum;
    }
    ADCaverage() : buf{0}
    {
        ADC_::ClockEnable();
    }
private:
    uint16_t buf[bufSize];
};

//////////////////////////////////////////////////////////////////////////////
// определение номера канала дма
//////////////////////////////////////////////////////////////////////////////
template<> const Channels channel<ADC1_t,DMA1stream0>() { return Channels::_0; }
template<> const Channels channel<ADC1_t,DMA1stream4>() { return Channels::_0; }

template<> const Channels channel<ADC2_t,DMA1stream2>() { return Channels::_1; }
template<> const Channels channel<ADC2_t,DMA1stream3>() { return Channels::_1; }

template<> const Channels channel<ADC3_t,DMA1stream0>() { return Channels::_2; }
template<> const Channels channel<ADC3_t,DMA1stream1>() { return Channels::_2; }

//////////////////////////////////////////////////////////////////////////////
// определение входного канала ацп (пока только uint8_t)
//////////////////////////////////////////////////////////////////////////////
template<> const uint8_t adcIn<ADC1_t,PA0>() { return 0;  }
template<> const uint8_t adcIn<ADC1_t,PA1>() { return 1;  }
template<> const uint8_t adcIn<ADC1_t,PA2>() { return 2;  }
template<> const uint8_t adcIn<ADC1_t,PA3>() { return 3;  }
template<> const uint8_t adcIn<ADC1_t,PA4>() { return 4;  }
template<> const uint8_t adcIn<ADC1_t,PA5>() { return 5;  }
template<> const uint8_t adcIn<ADC1_t,PA6>() { return 6;  }
template<> const uint8_t adcIn<ADC1_t,PA7>() { return 7;  }
template<> const uint8_t adcIn<ADC1_t,PB0>() { return 8;  }
template<> const uint8_t adcIn<ADC1_t,PB1>() { return 9;  }
template<> const uint8_t adcIn<ADC1_t,PC0>() { return 10; }
template<> const uint8_t adcIn<ADC1_t,PC1>() { return 11; }
template<> const uint8_t adcIn<ADC1_t,PC2>() { return 12; }
template<> const uint8_t adcIn<ADC1_t,PC3>() { return 13; }
template<> const uint8_t adcIn<ADC1_t,PC4>() { return 14; }
template<> const uint8_t adcIn<ADC1_t,PC5>() { return 15; }

template<> const uint8_t adcIn<ADC2_t,PA0>() { return 0;  }
template<> const uint8_t adcIn<ADC2_t,PA1>() { return 1;  }
template<> const uint8_t adcIn<ADC2_t,PA2>() { return 2;  }
template<> const uint8_t adcIn<ADC2_t,PA3>() { return 3;  }
template<> const uint8_t adcIn<ADC2_t,PA4>() { return 4;  }
template<> const uint8_t adcIn<ADC2_t,PA5>() { return 5;  }
template<> const uint8_t adcIn<ADC2_t,PA6>() { return 6;  }
template<> const uint8_t adcIn<ADC2_t,PA7>() { return 7;  }
template<> const uint8_t adcIn<ADC2_t,PB0>() { return 8;  }
template<> const uint8_t adcIn<ADC2_t,PB1>() { return 9;  }
template<> const uint8_t adcIn<ADC2_t,PC0>() { return 10; }
template<> const uint8_t adcIn<ADC2_t,PC1>() { return 11; }
template<> const uint8_t adcIn<ADC2_t,PC2>() { return 12; }
template<> const uint8_t adcIn<ADC2_t,PC3>() { return 13; }
template<> const uint8_t adcIn<ADC2_t,PC4>() { return 14; }
template<> const uint8_t adcIn<ADC2_t,PC5>() { return 15; }

template<> const uint8_t adcIn<ADC3_t,PA0>()  { return 0;  }
template<> const uint8_t adcIn<ADC3_t,PA1>()  { return 1;  }
template<> const uint8_t adcIn<ADC3_t,PA2>()  { return 2;  }
template<> const uint8_t adcIn<ADC3_t,PA3>()  { return 3;  }
template<> const uint8_t adcIn<ADC3_t,PF6>()  { return 4;  }
template<> const uint8_t adcIn<ADC3_t,PF7>()  { return 5;  }
template<> const uint8_t adcIn<ADC3_t,PF8>()  { return 6;  }
template<> const uint8_t adcIn<ADC3_t,PF9>()  { return 7;  }
template<> const uint8_t adcIn<ADC3_t,PF10>() { return 8;  }
template<> const uint8_t adcIn<ADC3_t,PF3>()  { return 9;  }
template<> const uint8_t adcIn<ADC3_t,PC0>()  { return 10; }
template<> const uint8_t adcIn<ADC3_t,PC1>()  { return 11; }
template<> const uint8_t adcIn<ADC3_t,PC2>()  { return 12; }
template<> const uint8_t adcIn<ADC3_t,PC3>()  { return 13; }
template<> const uint8_t adcIn<ADC3_t,PF4>()  { return 14; }
template<> const uint8_t adcIn<ADC3_t,PF5>()  { return 15; }


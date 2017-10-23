/**     Работа с ШИМ
 *      При объявление требует параметры шаблонов
 *          статический класс аппаратного таймера
 *          статический класс пина
 *      Конструктор инициализирует пин и таймер
 *      Пары таймер-пин конкретезируются путём инициализации константы channel для пары
 *      При неверном задании пары таймер-пин не компилируеться
 *      В этом файле конкретизируються только таймеры
 *          TIM2_t, TIM3_t, TIM4_t
 *      Если нужны другие, то необходимо дописать инициализацию channel
 */

#pragma once

#include <stdint.h>
#include "TIM_ral.h"
#include "pin_hal.h"





template <class Timer, class Pin>
class PWM
{
private:
    // частота в Гц
    uint16_t freq;
    // коэффициент заполнения в процентах
    uint16_t d;
    // таймер считает до, зависит от частоты
    uint32_t countTo;
    // номер канала, завивист от парты таймер-пин
    // инициализируеться для каждой парты тамер-пин
    static const uint8_t channel;

    void init (void)
    {
        Pin::Port::ClockEnable();
        Pin::Configure ( Pin::Mode::AlternateMode,
                         Pin::OutType::PushPull,
                         Pin::OutSpeed::High,
                         Pin::PullResistor::No);
        Pin::template SetAltFunc <Timer::AltFunc> ();
         
        Timer::ClockEnable();
        Timer::AutoReloadEnable();
        Timer::template SetCompareMode <Timer::CompareMode::PWMmode, channel> ();
        Timer::CounterEnable();
    }
public:
    PWM () : d(0)
    {
        init();
    }
    inline void outEnable (void)  { Timer::template CompareEnable <channel>(); }
    inline void outDisable (void) { Timer::template CompareDisable <channel>(); }
    inline bool isOutEnable ()    { return Timer::template IsCompareEnable<channel>(); }
    inline void setFreq (uint32_t f)
    {
        extern const uint32_t fCPU;
        if ( (f != this->freq) && (f != 0) ) {
            this->freq = f;
            countTo = fCPU / f - 1;
            Timer::SetAutoReloadValue (countTo);
            setD (d);
        }
    }
    // d - в процентах
    inline void setD (uint8_t d)
    {
        this->d = d;
        Timer::template SetCompareValue <channel> (countTo * d / 100);
    }
};


////////////////////////////////////////////////////
// конкретизация 
////////////////////////////////////////////////////


template<> const uint8_t PWM<TIM2_t,PA0>::channel  = 1;
template<> const uint8_t PWM<TIM2_t,PA1>::channel  = 2;
template<> const uint8_t PWM<TIM2_t,PA2>::channel  = 3;
template<> const uint8_t PWM<TIM2_t,PA3>::channel  = 4;
template<> const uint8_t PWM<TIM2_t,PA5>::channel  = 1;
template<> const uint8_t PWM<TIM2_t,PA15>::channel = 1;
template<> const uint8_t PWM<TIM2_t,PB3>::channel  = 2;
template<> const uint8_t PWM<TIM2_t,PB10>::channel = 3;
template<> const uint8_t PWM<TIM2_t,PB11>::channel = 4;

template<> const uint8_t PWM<TIM3_t,PA6>::channel  = 1;
template<> const uint8_t PWM<TIM3_t,PA7>::channel  = 2;
template<> const uint8_t PWM<TIM3_t,PB0>::channel  = 3;
template<> const uint8_t PWM<TIM3_t,PB1>::channel  = 4;
template<> const uint8_t PWM<TIM3_t,PB4>::channel  = 1;
template<> const uint8_t PWM<TIM3_t,PB5>::channel  = 2;
template<> const uint8_t PWM<TIM3_t,PC6>::channel  = 1;
template<> const uint8_t PWM<TIM3_t,PC7>::channel  = 2;
template<> const uint8_t PWM<TIM3_t,PC8>::channel  = 3;
template<> const uint8_t PWM<TIM3_t,PC9>::channel  = 4;

template<> const uint8_t PWM<TIM4_t,PB6>::channel  = 1;
template<> const uint8_t PWM<TIM4_t,PB7>::channel  = 2;
template<> const uint8_t PWM<TIM4_t,PB8>::channel  = 3;
template<> const uint8_t PWM<TIM4_t,PB9>::channel  = 4;
template<> const uint8_t PWM<TIM4_t,PD12>::channel = 1;
template<> const uint8_t PWM<TIM4_t,PD13>::channel = 2;
template<> const uint8_t PWM<TIM4_t,PD14>::channel = 3;
template<> const uint8_t PWM<TIM4_t,PD15>::channel = 4;




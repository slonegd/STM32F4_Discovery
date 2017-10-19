/**     Работа с ШИМ, абстракция от микроконтроллера
 *      При объявление требует параметры шаблонов
 *          статический класс аппаратного таймера
 *          статический класс пина
 *      Конструктор инициализирует пин и таймер
 *      Пары таймер и пин конкретезируються тут
 *      При неверном задании пары таймер пин не компилируеться
 *      В этом файле конкретизируються только таймеры
 *          TIM2_t, TIM3_t, TIM4_t
 *      Если нужны другие, то необходимо дописать
 */

#pragma once

#include <stdint.h>
#include "TIM_ral.h"
#include "pin_hal.h"



template <class Timer, class Pin>
class PWM
{
private:
    // таймер считает до, зависит от частоты
    uint32_t countTo;
    // сравнение с для ШИМ, зависит от частоты и от коэффициента заполнения
    uint32_t compare;
    void pinAndChannelInit (void);
public:
    PWM (void)
    {
        pinAndChannelInit();
        Timer::ClockEnable();
        Timer::AutoReloadEnable();
        Timer::template CompareEnable <3> ();
    }

    inline void start (void)
    {
        Timer::CounterEnable();
    }
    inline void stop (void)
    {
        Timer::CounterDisable();
        Pin::Clear();
    }
    inline void SetFreq (uint32_t f)
    {

    }
    inline void SetD (uint16_t d)
    {

    }

};

// для кокретизации шаблонных классов
template <class T, class P, uint8_t channel>
inline void concrate ()
{
    P::Port::ClockEnable();
    P::Configure ( P::Mode::AlternateMode,
                   P::OutType::PushPull,
                   P::OutSpeed::High,
                   P::PullResistor::No);
    P::template SetAltFunc <T::AltFunc> ();
    T::template SetCompareMode <T::CompareMode::PWMmode, channel> ();  
}

////////////////////////////////////////////////////
// конкретизация для TIM2
////////////////////////////////////////////////////
template<>
inline void PWM<TIM2_t, PA0>::pinAndChannelInit() { concrate <TIM2_t, PA0, 1> (); }
template<>
inline void PWM<TIM2_t, PA1>::pinAndChannelInit() { concrate <TIM2_t, PA1, 2> (); }
template<>
inline void PWM<TIM2_t, PA2>::pinAndChannelInit() { concrate <TIM2_t, PA2, 3> (); }

template<>
inline void PWM<TIM2_t, PA3>::pinAndChannelInit() { concrate <TIM2_t, PA3,4> (); }
template<>
inline void PWM<TIM2_t, PA5>::pinAndChannelInit() { concrate <TIM2_t, PA5, 1> (); }
template<>
inline void PWM<TIM2_t, PA15>::pinAndChannelInit() { concrate <TIM2_t, PA15, 1> (); }
template<>
inline void PWM<TIM2_t, PB3>::pinAndChannelInit() { concrate <TIM2_t, PB3, 2> (); }
template<>
inline void PWM<TIM2_t, PB10>::pinAndChannelInit() { concrate <TIM2_t, PB10, 3> (); }
template<>
inline void PWM<TIM2_t, PB11>::pinAndChannelInit() { concrate <TIM2_t, PB11, 4> (); }

////////////////////////////////////////////////////
// конкретизация для TIM3
////////////////////////////////////////////////////
template<>
inline void PWM<TIM3_t, PA6>::pinAndChannelInit() { concrate <TIM3_t, PA6, 1> (); }
template<>
inline void PWM<TIM3_t, PA7>::pinAndChannelInit() { concrate <TIM3_t, PA7, 2> (); }
template<>
inline void PWM<TIM3_t, PB0>::pinAndChannelInit() { concrate <TIM3_t, PB0, 3> (); }
template<>
inline void PWM<TIM3_t, PB1>::pinAndChannelInit() { concrate <TIM3_t, PB1, 4> (); }
template<>
inline void PWM<TIM3_t, PB4>::pinAndChannelInit() { concrate <TIM3_t, PB4, 1> (); }
template<>
inline void PWM<TIM3_t, PB5>::pinAndChannelInit() { concrate <TIM3_t, PB5, 2> (); }
template<>
inline void PWM<TIM3_t, PC6>::pinAndChannelInit() { concrate <TIM3_t, PC6, 1> (); }
template<>
inline void PWM<TIM3_t, PC7>::pinAndChannelInit() { concrate <TIM3_t, PC7, 2> (); }
template<>
inline void PWM<TIM3_t, PC8>::pinAndChannelInit() { concrate <TIM3_t, PC8, 3> (); }
template<>
inline void PWM<TIM3_t, PC9>::pinAndChannelInit() { concrate <TIM3_t, PC9, 4> (); }

////////////////////////////////////////////////////
// конкретизация для TIM4
////////////////////////////////////////////////////
template<>
inline void PWM<TIM4_t, PB6>::pinAndChannelInit() { concrate <TIM4_t, PB6, 1> (); }
template<>
inline void PWM<TIM4_t, PB7>::pinAndChannelInit() { concrate <TIM4_t, PB7, 2> (); }
template<>
inline void PWM<TIM4_t, PB8>::pinAndChannelInit() { concrate <TIM4_t, PB8, 3> (); }
template<>
inline void PWM<TIM4_t, PB9>::pinAndChannelInit() { concrate <TIM4_t, PB9, 4> (); }
template<>
inline void PWM<TIM4_t, PD12>::pinAndChannelInit() { concrate <TIM4_t, PD12, 1> (); }
template<>
inline void PWM<TIM4_t, PD13>::pinAndChannelInit() { concrate <TIM4_t, PD13, 2> (); }
template<>
inline void PWM<TIM4_t, PD14>::pinAndChannelInit() { concrate <TIM4_t, PD14, 3> (); }
template<>
inline void PWM<TIM4_t, PD15>::pinAndChannelInit() { concrate <TIM4_t, PD15, 4> (); }
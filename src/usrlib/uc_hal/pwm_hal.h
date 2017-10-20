/**     Работа с ШИМ
 *      При объявление требует параметры шаблонов
 *          статический класс аппаратного таймера
 *          статический класс пина
 *      Конструктор инициализирует пин и таймер
 *      Пары таймер-пин конкретезируются пустой функцией concretize
 *      При неверном задании пары таймер-пин не компилируеться
 *      В этом файле конкретизируються только таймеры
 *          TIM2_t, TIM3_t, TIM4_t
 *      Если нужны другие, то необходимо дописать (есть макрос)
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
    // для кокретизации пары таймер-пин
    void concretize (void);
    static const uint8_t channel;
public:
    PWM (void)
    {
        concretize();

        Pin::Port::ClockEnable();
        Pin::Configure ( Pin::Mode::AlternateMode,
                         Pin::OutType::PushPull,
                         Pin::OutSpeed::High,
                         Pin::PullResistor::No);
        Pin::template SetAltFunc <Timer::AltFunc> ();
         
        Timer::ClockEnable();
        Timer::AutoReloadEnable();
        Timer::template CompareEnable <channel> ();
        Timer::template SetCompareMode <Timer::CompareMode::PWMmode, channel> ();
        Timer::CounterEnable();
    }

    inline void start (void)
    {
        Timer::template CompareEnable <channel>();
    }
    inline void stop (void)
    {
        Timer::template CompareDisable <channel>();
//        Pin::Clear();
    }
    inline bool IsCompareEnable ()
    {
        return Timer::template IsCompareEnable<channel>();
    }
    inline void SetFreq (uint32_t f)
    {
        // временно
        Timer::SetAutoReloadValue(f);
    }
    inline void SetD (uint16_t d)
    {

    }
private:

};

#define CONCRETIZE(Timer, Pin, Channel) template<> \
    inline void PWM<Timer, Pin>::concretize() { } \
    template<> \
    const uint8_t PWM<Timer, Pin>::channel = Channel

////////////////////////////////////////////////////
// конкретизация 
////////////////////////////////////////////////////
CONCRETIZE (TIM2_t, PA0,  1);
CONCRETIZE (TIM2_t, PA1,  2);
CONCRETIZE (TIM2_t, PA2,  3);
CONCRETIZE (TIM2_t, PA3,  4);
CONCRETIZE (TIM2_t, PA5,  1);
CONCRETIZE (TIM2_t, PA15, 1);
CONCRETIZE (TIM2_t, PB3,  2);
CONCRETIZE (TIM2_t, PB10, 3);
CONCRETIZE (TIM2_t, PB11, 4);
CONCRETIZE (TIM3_t, PA6,  1);
CONCRETIZE (TIM3_t, PA7,  2);
CONCRETIZE (TIM3_t, PB0,  3);
CONCRETIZE (TIM3_t, PB1,  4);
CONCRETIZE (TIM3_t, PB4,  1);
CONCRETIZE (TIM3_t, PB5,  2);
CONCRETIZE (TIM3_t, PC6,  1);
CONCRETIZE (TIM3_t, PC7,  2);
CONCRETIZE (TIM3_t, PC8,  3);
CONCRETIZE (TIM3_t, PC9,  4);
CONCRETIZE (TIM4_t, PB6,  1);
CONCRETIZE (TIM4_t, PB7,  2);
CONCRETIZE (TIM4_t, PB8,  3);
CONCRETIZE (TIM4_t, PB9,  4);
CONCRETIZE (TIM4_t, PD12, 1);
CONCRETIZE (TIM4_t, PD13, 2);
CONCRETIZE (TIM4_t, PD14, 3);
CONCRETIZE (TIM4_t, PD15, 4);

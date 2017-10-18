/**
 * Работа с ШИМ, абстракция от микроконтроллера
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


// пока делаю конкретизацию только для TIM2
template<>
inline void PWM<TIM2_t, Pin_t<PA,1> >::pinAndChannelInit()
{
    Pin_t<PA,1>::Port::ClockEnable();
    Pin_t<PA,1>::Configure ( Pin_t<PA,1>::Mode::AlternateMode,
                             Pin_t<PA,1>::OutType::PushPull,
                             Pin_t<PA,1>::OutSpeed::High,
                             Pin_t<PA,1>::PullResistor::No);
    Pin_t<PA,1>::SetAltFunc<Pin_t<PA,1>::AF::AF1>();
}

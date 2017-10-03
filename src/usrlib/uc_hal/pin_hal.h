/**
 * HAL над работой с пинами микроконтроллера
 * представляет из себя шаблонный класс со стандартными статическими функциями
 * параметры функции Configure() зависят от контроллера,
 * от этого никуда не деться.
 * Первый параметр шаблона выбираеться из классов портов,
 * описнныз в GPIO_ral.h
 */

#pragma once

#include "stm32f4_ral/GPIO_ral.h"


template <class PORT, uint8_t pin>
class Pin_t : protected PORT
{
public:
    inline static void Configure ( GPIO_t::Mode_t mode,
                                   GPIO_t::OutType_t type,
                                   GPIO_t::OutSpeed_t speed,
                                   GPIO_t::PullResistor_t res)
    {
        PORT::mode().reg    &= ~((uint32_t)0b11 << pin*2);
        PORT::mode().reg    |=  (uint32_t)mode  << pin*2;
        PORT::otype().reg   &= ~((uint32_t)0b1  << pin);
        PORT::otype().reg   |=  (uint32_t)type  << pin;
        PORT::ospeed().reg  &= ~((uint32_t)0b11 << pin*2);
        PORT::ospeed().reg  |=  (uint32_t)speed << pin*2;
        PORT::pupd().reg    &= ~((uint32_t)0b1  << pin);
        PORT::pupd().reg    |=  (uint32_t)res   << pin;
    }

    inline static bool IsSet (void)
    {
        return ( PORT::id().reg & (uint16_t)1<<pin );
    }

    inline static void Set (void)
    {
        PORT::WriteSet (1<<pin);
    }
    inline static void Reset (void)
    {
        PORT::WriteReset (1<<pin);
    }
    inline static void Invert (void)
    {
        if ( IsSet() ) {
            Reset();
        } else {
            Set();
        }
    }
};



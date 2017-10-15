/**
 * HAL над работой с пинами микроконтроллера
 * представляет из себя шаблонный класс со стандартными статическими функциями
 * параметры функции Configure() зависят от контроллера,
 * от этого никуда не деться.
 * Первый параметр шаблона выбираеться из классов портов,
 * описнныз в GPIO_ral.h
 */

#pragma once

#include "port_hal.h"
#include <stdint.h>
#include <stdbool.h>


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

    // мои старые методы
    static void Reset() { PORT::WriteReset (1<<pin); }
    static void Invert()
    {
        if ( IsSet() ) {
            Reset();
        } else {
            Set();
        }
    }

    // далее идут поля для интеграции с Mcucpp
    typedef PORT Port;
    static const unsigned Number = pin;
    static const bool Inverted = false;

    static void Set()           { PORT::template Set<1u << pin> (); }
    static void Clear()         { PORT::template Clear<1u << pin> (); }
    static void Toggle()        { PORT::template Toggle<1u << pin> (); }
    static void Set(bool b)
    {
        if (b) {
            Set();
        } else {
            Clear();
        }
    }
    static bool IsSet()        { return ( (PORT::PinRead() & (1u << pin) ) != 0); }
    static void WaitForSet()   { while( IsSet() == 0) {} }
    static void WaitForClear() { while( IsSet() ) {} }

    // конфигурацию пока оставлю как есть
    /*
    static void SetDir(uint8_t val);
   
    static void SetDirRead();
    static void SetDirWrite();
    static void SetConfiguration(Configuration configuration);
    
    static void SetDriverType(DriverType driverType);
    static void SetPullUp(PullMode pullMode);
    static void SetSpeed(Speed speed);
    static void AltFuncNumber(uint8_t funcNumber);

    template<Configuration configuration>
    static void SetConfiguration()
    {
        ConfigPort:: template SetConfiguration<1 << PIN, configuration>();
    }
    */



};



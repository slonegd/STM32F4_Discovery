/**
 * Библиотека классов выводов мс
 * Каждый вывод предствлен в виде отдельного статического класса
 * и может быть передан в качестве параметра шаблона
 */

#include "ports.hpp"
#include "pins_AF.h"

#ifndef PINS_HPP
#define PINS_HPP

template <class PORT, uint8_t pin>
class Tpin : private PORT
{
public:
    inline static void SetModer (Mode_t Mode) 
    { 
        PORT::moder() &= ~((uint32_t)0b11 << (pin*2));
        PORT::moder() |= (uint32_t)Mode << (pin*2);
    } 
    inline static void SetOutputType (OutputType_t Type) 
    {
        PORT::otyper() &= ~((uint32_t)0b1 << pin);
        PORT::otyper() |= (uint32_t)Type << pin;
    } 
    inline static void SetOutputSpeed (OutputSpeed_t Speed) 
    {
        PORT::ospeedr() &= ~((uint32_t)0b11 << (pin*2));
        PORT::ospeedr() |= (uint32_t)Speed << (pin*2);
    } 
    inline static void SetPullResistor (PullResistor_t Pull) 
    {
        PORT::pupdr() &= ~((uint32_t)0b11 << (pin*2));
        PORT::pupdr() |= (uint32_t)Pull << (pin*2);
    } 
    inline static void Set (void) 
    { 
        PORT::bsrr() = (uint32_t)1<<pin; 
    } 
    inline static void Reset (void) 
    { 
        PORT::bsrr() = (uint32_t)1<<(pin+16); 
    } 
    inline static bool IsSet (void) 
    { 
        return ( PORT::idr() & (uint32_t)1<<pin ); 
    } 
    inline static void Invert (void) 
    { 
        if ( IsSet() ) { 
            Reset (); 
        } else { 
            Set (); 
        } 
    } 
};   


#endif // PINS_HPP
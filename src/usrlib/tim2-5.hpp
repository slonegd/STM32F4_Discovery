/**
 * Библиотека классов таймеров со 2 по 5
 * Каждый таймер предствлен в виде отдельного статического класса
 * и может быть передан в качестве параметра шаблона
 */

#include "stm32f4_bf.h"
#include "stm32f4_llul.h"

#ifndef TIM2_5_HPP
#define TIM2_5_HPP

#define MAKE_STATIC_CLASS_T(N) \
    class T##N \
    { \
    private: \
        static volatile TIM2_5_CR1_t &cr1() { \
            return (TIM2_5_CR1_t &)TIM##N->CR1; \
        } \
    public: \
        inline static void CountEnable (void) \
        { \
            cr1().CEN = 1; \
        } \
        inline static void CountDisable (void) \
        { \
            cr1().CEN = 0; \
        } \
    }

    MAKE_STATIC_CLASS_T(2);
    MAKE_STATIC_CLASS_T(3);
    MAKE_STATIC_CLASS_T(4);
    MAKE_STATIC_CLASS_T(5);

#endif // TIM2_5_HPP
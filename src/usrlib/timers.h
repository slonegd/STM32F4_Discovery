/**
 * класс аппаратных таймеров
 * объекты класса - отдельные таймеры
 * статические методы - общее для всех таймеров:
 *      Timers::msHardvareInit - включение аппаратного таймера
 *          на прерывание каждую милисекунду
 *      Timers::tick - должна вызываться в прерывании этого таймера
 *          инкрементирует скрытую служебную переменную
 *      Timers::update - обновляет, если надо, все поля созданных таймеров
 * 
 * maxTimerQty ограничивает количество таймеров
 * 
 */

#pragma once

#include <stdint.h>
#include "uc_hal/sysTick_hal.h"

static const uint8_t maxTimerQty = 10;

class Timers
{
private:
    // разрешение работы, таймер считает и устанавливает Q
	// если IN == true	
	volatile bool IN;
	// время работы в мс до установки Q, если IN == true
	volatile uint32_t PT;
	// прошедшее время в мс, если IN == true
	volatile uint32_t ET;	
	// флаг, что установленное время прошло
    volatile bool Q;
    // служебная переменная, подсчёт милисекунд
    static volatile uint16_t TickCount;
    // массив указателей на все таймеры, используеться в методе update
    static Timers* all[maxTimerQty];
    // количество созданныз объектов, не должно превышать maxTimerQty
    static uint8_t qty;
public:
    Timers (void)
    {
        all[qty++] = this;
    }
    static inline void msHardvareInit (void)
    {
        InitSysTimerInt<1> ();
    }
    static inline void update (void)
    {
        if (TickCount > 0) {
            for (uint8_t i = 0; i < qty; i++) {
                all[i]->ET = (all[i]->IN && (all[i]->ET < all[i]->PT))
                                ? all[i]->ET+TickCount : all[i]->ET;
                all[i]->Q = ( (all[i]->ET >= all[i]->PT) && all[i]->IN )
                                ? true : false;
            }
            TickCount = 0;
        }
    }
    inline void setTimeAndStart (uint32_t ms)
    {
        PT = ms;
        IN = true;
    }
    static inline void tick (void)
    {
        TickCount++;
    }
    inline bool event (void)
    {
        if (Q) {
            Q = false;
            ET = 0;
            return (true);
        } else {
            return (false);
        }
    }
};

volatile uint16_t Timers::TickCount = 0;
uint8_t Timers::qty = 0;
Timers* Timers::all[maxTimerQty] = {0};


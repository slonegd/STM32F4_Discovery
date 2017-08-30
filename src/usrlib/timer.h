/**
 * Програмный таймер с дискретностью 1 мс
 * 
 * Количество таймеров долно быть определено константой QtyTimers,
 * которая является частью перечисления eTimer_t, которое должно быть
 * определено, например в init.h. Пример:
 * 		typedef enum {
 *  		timer1 = 0,
 * 			timer2,
 *    		QtyTimers
 * 		} eTimer_t;
 * 
 * Один таймер хранится в памяти в виде stTimer_t
 * объявление таймеров в этом файле
 * для обращения к членам таймера в других файлах, использовать
 * extern stTimer_t Timers[QtyTimers];
 * !!! НО это не рекомендуеться, есть функции
 * 
 * В прерывании инкрементировать буферную переменну,
 * по велечине которой функция TimersUpdate оьновляет все таймеры
 * функцию TimersUpdate необходимо вызывать
 * 
 * должен быть определен макрос F_CPU (например в defines.h)
 * 
 * обработчик прерывания тут SysTick_Handler,
 * если необходимо перенести в другой файл,
 * то обязательно следующее
 * 		void SysTick_Handler (void)
 * 		{
 * 			extern volatile uint32_t TickCount;
 *   		TickCount++;
 *			//далее добавить, что нужно
 *		}
 */

#include <stdint.h>
#include <stdbool.h>
#include "../defines.h"
#include "../inc/stm32f4xx.h"

#ifndef TIMER_H_
#define TIMER_H_

#define TIMER_1MS	F_CPU/1000-1

/**
 * структура экземпляра таймера
 * логика и наименования как в Codesys
 * без volatile не работает
 */
typedef struct {
	/**
	 * разрешение работы, таймер считыет и устанавливает Q
	 * если IN == true
	 */	
	volatile bool IN;
	/**
	 * время работы в мс до установки Q, если IN == true
	 */
	volatile uint32_t PT;
	/**
	 * прошедшее время в мс, если IN == true,
	 * инкрементируется аппаратным таймером 
	 * (функция TimerTick)
	 */
	volatile uint32_t ET;	
	/**
	 * флаг, что установленное время прошло,
	 * устанавливается только при вызове макроса TIMER_UPDATE()
	 * если IN == true;
	 * сбрасывается макросом TIMER_STOP() или TIMER_RESET()
	 */
	volatile bool Q;			
} stTimer_t;

stTimer_t Timers[QtyTimers];
volatile uint32_t TickCount = 0;

/**
 * инициализация аппаратного таймера на 1 мс
 */
inline void TimerInit (void)
{
	SysTick->LOAD = TIMER_1MS;						//Загрузка значения
	SysTick->VAL = TIMER_1MS;						//Обнуляем таймеры и флаги 

	SysTick->CTRL =	SysTick_CTRL_CLKSOURCE_Msk 		//processor clock
					| SysTick_CTRL_TICKINT_Msk;		//разрешение прерывания
	
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;  	//запускает таймер
	return;		
}

inline void TimerSetTime (eTimer_t N, uint32_t ms)
{
	Timers[N].PT = ms;
}
inline void TimerStart (eTimer_t N)
{
	Timers[N].IN = true;
}
inline void TimerStop (eTimer_t N)
{
	Timers[N].IN = false;
	Timers[N].Q = false;
	Timers[N].ET = 0;
}
inline void TimerPause (eTimer_t N)
{
	Timers[N].IN = false;
}
inline void TimerReset (eTimer_t N)
{
	Timers[N].Q = 0; 
	Timers[N].ET = 0;
}

// обновляейт таймеры (члены структурыы Q и ET)
inline void TimersUpdate ()
{
	if (TickCount > 0) {
		for (uint8_t i = 0; i < QtyTimers; i++) {
			Timers[i].ET = (Timers[i].IN && (Timers[i].ET < Timers[i].PT))
							? Timers[i].ET+TickCount : Timers[i].ET;
			Timers[i].Q = ( (Timers[i].ET >= Timers[i].PT) && Timers[i].IN )
							? true : false;
		}
		TickCount = 0;
	}
}

// Возвращает true, если флаг Q установлен,
// и после чего перезапускает таймер
inline bool TimerEvent (eTimer_t N)
{
	if (Timers[N].Q) {
		Timers[N].Q = 0;
		Timers[N].ET = 0;
		return (true);
	} else {
		return (false);
	}
}

/****************************************************************************
 * прерываниe
 ***************************************************************************/
void SysTick_Handler (void)
{
    TickCount++;
}	

#endif // TIMER_H_
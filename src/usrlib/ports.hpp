/**
 * не вышло, компилируется, но при отладке уходит в инфинитилуп 
 * по неизвестному вектору прерываний
 *
 */

#include "stm32f4_bf.h"
#include "stm32f4_llul.h"

#ifndef PORTC_HPP
#define PORTC_HPP



class PA 
{
private:
//	static GPIO_MODER_t* MODER = (GPIO_MODER_t*) (&(GPIOA->MODER));
	static volatile GPIO_MODER_t &moder()
	{
		return (GPIO_MODER_t &)GPIOA->MODER;
	}
public:
	inline static void SetModer (eMode_t Mode)
	{
		moder().MODER2 = Mode;
	}
};

#endif // PORTC_HPP
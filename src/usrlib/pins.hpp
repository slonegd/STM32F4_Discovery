/**
 * Библиотека классов выводов мс
 * Каждый вывод предствлен в виде отдельного статического класса
 * и может быть передан в качестве параметра шаблона
 */

#include "ports.hpp"
#include "pins_AF.h"

#ifndef PINS_HPP
#define PINS_HPP

#define MAKE_STATIC_CLASS_PIN(PORT,PINN) \
	class PORT##PINN \
	{ \
	public: \
		inline static void SetModer (eMode_t Mode) \
		{ \
			PORT::moder().MODER##PINN = Mode; \
		} \
		inline static void SetOutputType (eOutputType_t Type) \
		{ \
			PORT::otyper().OT##PINN = Type; \
		} \
		inline static void SetOutputSpeed (eOutputSpeed_t Speed) \
		{ \
			PORT::ospeedr().OSPEEDR##PINN = Speed; \
		} \
		inline static void SetPullResistor (ePullResistor_t Pull) \
		{ \
			PORT::pupdr().PUPDR##PINN = Pull; \
		} \
		inline static void Set (void) \
		{ \
			PORT::bsrr() = (uint32_t)1<<PINN; \
		} \
		inline static void Reset (void) \
		{ \
			PORT::bsrr() = (uint32_t)1<<(PINN+16); \
		} \
		inline static bool IsSet (void) \
		{ \
			return ( PORT::odr().ODR##PINN ); \
		} \
		inline static void Invert (void) \
		{ \
			if ( IsSet() ) { \
				Reset (); \
			} else { \
				Set (); \
			} \
		} \
	} // class PORT##PINN					

#define MAKE_ALL_PINS_IN_PORT(PORT)	\
	MAKE_STATIC_CLASS_PIN (PORT,0);	\
	MAKE_STATIC_CLASS_PIN (PORT,1);	\
	MAKE_STATIC_CLASS_PIN (PORT,2);	\
	MAKE_STATIC_CLASS_PIN (PORT,3);	\
	MAKE_STATIC_CLASS_PIN (PORT,4);	\
	MAKE_STATIC_CLASS_PIN (PORT,5);	\
	MAKE_STATIC_CLASS_PIN (PORT,6);	\
	MAKE_STATIC_CLASS_PIN (PORT,7);	\
	MAKE_STATIC_CLASS_PIN (PORT,8);	\
	MAKE_STATIC_CLASS_PIN (PORT,9);	\
	MAKE_STATIC_CLASS_PIN (PORT,10); \
	MAKE_STATIC_CLASS_PIN (PORT,11); \
	MAKE_STATIC_CLASS_PIN (PORT,12); \
	MAKE_STATIC_CLASS_PIN (PORT,13); \
	MAKE_STATIC_CLASS_PIN (PORT,14); \
	MAKE_STATIC_CLASS_PIN (PORT,15);

MAKE_ALL_PINS_IN_PORT(PA);
MAKE_ALL_PINS_IN_PORT(PB);
MAKE_ALL_PINS_IN_PORT(PC);
MAKE_ALL_PINS_IN_PORT(PD);
MAKE_ALL_PINS_IN_PORT(PE);
MAKE_ALL_PINS_IN_PORT(PF);
MAKE_ALL_PINS_IN_PORT(PG);
MAKE_ALL_PINS_IN_PORT(PH);
MAKE_ALL_PINS_IN_PORT(PI);

#endif // PINS_HPP
#pragma once
#ifndef DEFINES_H
#define DEFINES_H

#include "usrlib/ports.hpp"
#include "usrlib/pins.hpp"

#define F_CPU   168000000UL

typedef enum {
	BledTimer	= 0,
	RledTimer,
	OledTimer,
	GledTimer,
	QtyTimers
} eTimer_t;

// discoveri leds
typedef PD LedPort;
typedef Tpin<PD,15> Bled;
typedef Tpin<PD,14> Rled;
typedef Tpin<PD,13> Oled;
typedef Tpin<PD,12> Gled;


#endif // DEFINES_H
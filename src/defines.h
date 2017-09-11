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
typedef PD15 Bled;
typedef PD14 Rled;
typedef PD13 Oled;
typedef PD12 Gled;

#endif // DEFINES_H
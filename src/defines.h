#ifndef DEFINES_H
#define DEFINES_H

#define F_CPU   168000000UL

typedef enum {
	BledTimer	= 0,
	RledTimer,
	OledTimer,
	GledTimer,
	QtyTimers
} eTimer_t;

// discoveri leds
#define LED_PORT GPIOD
#define BLED_PIN 15
#define RLED_PIN 14
#define OLED_PIN 13
#define GLED_PIN 12

#endif // DEFINES_H
#ifndef INT_H
#define INT_H

#include <stdint.h>
#include <mmu.h>

#define INT_VBLANK	(1 << 0)
#define INT_LCD		(1 << 1)
#define INT_TIMER	(1 << 2)
#define INT_SERIAL	(1 << 3)
#define INT_JOYPAD	(1 << 4)

typedef struct m_interrupt
{
	uint8_t m_master;
	uint8_t m_enabled;
	uint8_t m_flags;
} m_interrupts;

extern m_interrupts interrupts;

#endif
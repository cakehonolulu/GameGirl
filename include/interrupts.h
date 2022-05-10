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
#if !defined(PREC23)
	unsigned _BitInt(1) m_master;
#else
	uint8_t m_master;
#endif
	uint8_t m_enabled;
	uint8_t m_flags;
} m_interrupts;

extern m_interrupts interrupts;

#define IME (interrupts.m_master)
#define IE (interrupts.m_enabled)
#define IF (interrupts.m_flags)

void m_interrupt_check();

#endif
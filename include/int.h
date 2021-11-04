#include <stdint.h>
#include "mmu.h"

typedef struct m_int
{
	uint8_t m_master;
	uint8_t m_enabled;
	uint8_t m_flags;
} m_interrupts;

extern m_interrupts ints;
#include <stdint.h>
#include <stddef.h>
#include "gamegirl.h"
#include "mmu.h"

struct m_sharp_lr35902_instr_cb {
	char *m_instr;
	void *m_funct;
} extern const m_gb_instr_cb[256];

// 0x7C
void m_bit_7_h();

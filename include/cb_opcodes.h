#include <stdint.h>
#include <stddef.h>
#include <gamegirl.h>
#include <mmu.h>
#include <cycle.h>
#include <bit/bits.h>

extern struct m_sharp_lr35902_instr_cb {
	char *m_instr;
	void *m_funct;
} const m_gb_instr_cb[256];

// 0x11
void m_rl_c();

// 0x7C
void m_bit_7_h();

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

void m_cb_ext(m_dmg_t *m_dmg, uint8_t cb_instr);

// 0x11
void m_rl_c(m_dmg_t *m_dmg);

// 0x37
void m_swap_a(m_dmg_t *m_dmg);

// 0x7C
void m_bit_7_h(m_dmg_t *m_dmg);

// 0xFE
void m_set_7_parhl(m_dmg_t *m_dmg);

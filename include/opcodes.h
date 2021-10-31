#include <stdint.h>
#include <stddef.h>
#include "gamegirl.h"
#include "mmu.h"

struct m_sharp_lr35902_instr {
	char *m_instr;
	uint8_t m_operand;
	void *m_funct;
} extern const m_gb_instr[256];

// 0x00
void m_nop();

// 0x0E
void m_ld_c_d8();

// 0x20
void m_jr_nz_s8();

// 0x21
void m_ld_hl_d16();

// 0x31
void m_ld_sp_d16();

// 0x32
void m_ld_hlminus_a();

// 0x3E
void m_ld_a_d8();

// 0xAF
void m_xor_a();

// 0xCB
extern void m_cb_ext();

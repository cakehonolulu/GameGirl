#include <stdint.h>
#include <stddef.h>
#include "gamegirl.h"
#include "mmu.h"

struct m_sharp_lr35902_instr {
	char *m_instr;
	void *m_funct;
} extern const m_gb_instr[256];

// 0x00
void m_nop();

// 0x20
void m_jr_nz_s8();

// 0x21
void m_ld_hl_d16();

// 0x31
void m_ld_sp_d16();

// 0x32
void m_ld_hlminus_a();

// 0xAF
void m_xor_a();
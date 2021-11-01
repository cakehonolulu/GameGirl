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

// 0x06
void m_ld_b_d8();

// 0x0C
void m_inc_c();

// 0x0E
void m_ld_c_d8();

// 0x11
void m_ld_de_d16();

// 0x17
void m_rla();

// 0x1A
void m_ld_a_de();

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

// 0x4F
void m_ld_c_a();

// 0x77
void m_ld_hl_a();

// 0xAF
void m_xor_a();

// 0xC0
void m_ret_nz();

// 0xC1
void m_pop_bc();

// 0xC5
void m_push_bc();

// 0xCB
extern void m_cb_ext();

// 0xCD
void m_call();

// 0xE0
void m_ld_a8_a();

// 0xE2
void m_ld_cpar_a();

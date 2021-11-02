#include <stdint.h>
#include <stddef.h>
#include "gamegirl.h"
#include "mmu.h"
#include "cycle.h"

struct m_sharp_lr35902_instr {
	char *m_instr;
	uint8_t m_operand;
	void *m_funct;
} extern const m_gb_instr[256];

// 0x00
void m_nop();

// 0x04
void m_inc_b();

// 0x05
void m_dec_b();

// 0x06
void m_ld_b_d8(uint8_t m_d8);

// 0x0C
void m_inc_c();

// 0x0D
void m_dec_c();

// 0x0E
void m_ld_c_d8(uint8_t m_d8);

// 0x11
void m_ld_de_d16(uint16_t m_d16);

// 0x13
void m_inc_de();

// 0x17
void m_rla();

// 0x18
void m_jr_s8(int8_t m_s8);

// 0x1A
void m_ld_a_de();

// 0x20
void m_jr_nz_s8(int8_t m_s8);

// 0x21
void m_ld_hl_d16(uint16_t m_d16);

// 0x22
void m_ld_hlplus_a();

// 0x23
void m_inc_hl();

// 0x28
void m_jr_z_s8(int8_t m_s8);

// 0x2E
void m_ld_l_d8(uint8_t m_d8);

// 0x31
void m_ld_sp_d16(uint16_t m_d16);

// 0x32
void m_ld_hlminus_a();

// 0x3D
void m_dec_a();

// 0x3E
void m_ld_a_d8(uint8_t m_d8);

// 0x4F
void m_ld_c_a();

// 0x57
void m_ld_d_a();

// 0x67
void m_ld_h_a();

// 0x77
void m_ld_hl_a();

// 0x7B
void m_ld_a_e();

// 0xAF
void m_xor_a();

// 0xC0
void m_ret_nz();

// 0xC1
void m_pop_bc();

// 0xC5
void m_push_bc();

// 0xC9
void m_ret();

// 0xCB
extern void m_cb_ext();

// 0xCD
void m_call(uint16_t m_addr);

// 0xE0
void m_ld_a8_a(uint8_t m_a8);

// 0xE2
void m_ld_cpar_a();

// 0xEA
void m_ld_a16_a(uint16_t m_a16);

// 0xFE
void m_cp_d8(uint8_t m_d8);
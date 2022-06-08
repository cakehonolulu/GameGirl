#include <stdint.h>
#include <stddef.h>
#include <mmu.h>
#include <cycle.h>
#include <interrupts.h>
#include <alu.h>
#include <stack.h>
#include <gamegirl.h>

extern struct m_sharp_lr35902_instr {
	char *m_instr;
	uint8_t m_operand;
	void *m_funct;
} const m_gb_instr[256];

// 0x00
void m_nop(m_dmg_t *m_dmg);

// 0x01
void m_ld_bc_d16(m_dmg_t *m_dmg, uint16_t m_d16);

// 0x04
void m_inc_b(m_dmg_t *m_dmg);

// 0x05
void m_dec_b(m_dmg_t *m_dmg);

// 0x06
void m_ld_b_d8(m_dmg_t *m_dmg, uint8_t m_d8);

// 0x0B
void m_dec_bc(m_dmg_t *m_dmg);

// 0x0C
void m_inc_c(m_dmg_t *m_dmg);

// 0x0D
void m_dec_c(m_dmg_t *m_dmg);

// 0x0E
void m_ld_c_d8(m_dmg_t *m_dmg, uint8_t m_d8);

// 0x11
void m_ld_de_d16(m_dmg_t *m_dmg, uint16_t m_d16);

// 0x13
void m_inc_de(m_dmg_t *m_dmg);

// 0x15
void m_dec_d(m_dmg_t *m_dmg);

// 0x16
void m_ld_d_d8(m_dmg_t *m_dmg, uint8_t m_d8);

// 0x17
void m_rla(m_dmg_t *m_dmg);

// 0x18
void m_jr_s8(m_dmg_t *m_dmg, int8_t m_s8);

// 0x19
void m_add_hl_de(m_dmg_t *m_dmg);

// 0x1A
void m_ld_a_de(m_dmg_t *m_dmg);

// 0x1D
void m_dec_e(m_dmg_t *m_dmg);

// 0x1E
void m_ld_e_d8(m_dmg_t *m_dmg, uint8_t m_d8);

// 0x20
void m_jr_nz_s8(m_dmg_t *m_dmg, int8_t m_s8);

// 0x21
void m_ld_hl_d16(m_dmg_t *m_dmg, uint16_t m_d16);

// 0x22
void m_ld_hlplus_a(m_dmg_t *m_dmg);

// 0x23
void m_inc_hl(m_dmg_t *m_dmg);

// 0x24
void m_inc_h(m_dmg_t *m_dmg);

// 0x28
void m_jr_z_s8(m_dmg_t *m_dmg, int8_t m_s8);

// 0x2A
void m_ld_a_hlplusp(m_dmg_t *m_dmg);

// 0x2E
void m_ld_l_d8(m_dmg_t *m_dmg, uint8_t m_d8);

// 0x2F
void m_cpl(m_dmg_t *m_dmg);

// 0x31
void m_ld_sp_d16(m_dmg_t *m_dmg, uint16_t m_d16);

// 0x32
void m_ld_hlminus_a(m_dmg_t *m_dmg);

// 0x36
void m_ld_hlp_d8(m_dmg_t *m_dmg, uint8_t m_d8);

// 0x3D
void m_dec_a(m_dmg_t *m_dmg);

// 0x3E
void m_ld_a_d8(m_dmg_t *m_dmg, uint8_t m_d8);

// 0x47
void m_ld_b_a(m_dmg_t *m_dmg);

// 0x4F
void m_ld_c_a(m_dmg_t *m_dmg);

// 0x57
void m_ld_d_a(m_dmg_t *m_dmg);

// 0x5F
void m_ld_e_a(m_dmg_t *m_dmg);

// 0x67
void m_ld_h_a(m_dmg_t *m_dmg);

// 0x77
void m_ld_hl_a(m_dmg_t *m_dmg);

// 0x78
void m_ld_a_b(m_dmg_t *m_dmg);

// 0x79
void m_ld_a_c(m_dmg_t *m_dmg);

// 0x7B
void m_ld_a_e(m_dmg_t *m_dmg);

// 0x7C
void m_ld_a_h(m_dmg_t *m_dmg);

// 0x7D
void m_ld_a_l(m_dmg_t *m_dmg);

// 0x86
void m_ld_a_phl(m_dmg_t *m_dmg);

// 0x87
void m_add_a_a(m_dmg_t *m_dmg);

// 0x90
void m_sub_b(m_dmg_t *m_dmg);

// 0xA1
void m_and_c(m_dmg_t *m_dmg);

// 0xA9
void m_xor_c(m_dmg_t *m_dmg);

// 0xAF
void m_xor_a(m_dmg_t *m_dmg);

// 0xB0
void m_or_b(m_dmg_t *m_dmg);

// 0xB1
void m_or_c(m_dmg_t *m_dmg);

// 0xBE
void m_cp_hl(m_dmg_t *m_dmg);

// 0xC1
void m_pop_bc(m_dmg_t *m_dmg);

// 0xC3
void m_jp_a16(m_dmg_t *m_dmg, uint16_t m_a16);

// 0xC5
void m_push_bc(m_dmg_t *m_dmg);

// 0xC9
void m_ret(m_dmg_t *m_dmg);

// 0xCB
// CB_EXT

// 0xCD
void m_call(m_dmg_t *m_dmg, uint16_t m_addr);

// 0xE0
void m_ld_a8_a(m_dmg_t *m_dmg, uint8_t m_a8);

// 0xE1
void m_pop_hl(m_dmg_t *m_dmg);

// 0xE2
void m_ld_cpar_a(m_dmg_t *m_dmg);

// 0xE6
void m_and_d8(m_dmg_t *m_dmg, uint8_t m_d8);

// 0xEA
void m_ld_a16_a(m_dmg_t *m_dmg, uint16_t m_a16);

// 0xEF
void m_rst_5(m_dmg_t *m_);

// 0xF0
void m_ld_a_a8(m_dmg_t *m_dmg, uint8_t m_a8);

// 0xF3
void m_di(m_dmg_t *m_dmg);

// 0xFB
void m_ei(m_dmg_t *m_dmg);

// 0xFE
void m_cp_d8(m_dmg_t *m_dmg, uint8_t m_d8);

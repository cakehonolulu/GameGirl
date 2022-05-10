#include <opcodes.h>

// Operand Methodology Inspired by CTurt
const struct m_sharp_lr35902_instr m_gb_instr[256] = {
	{"NOP", 0, m_nop},						   // 0x00
	{"LD BC, ", 2, m_ld_bc_d16},			   // 0x01
	{NULL, 0, NULL},                           // 0x02
	{NULL, 0, NULL},                           // 0x03
	{"INC B", 0, m_inc_b},                           // 0x04
	{"DEC B", 0, m_dec_b},                     // 0x05
	{"LD B, ", 1, m_ld_b_d8},                  // 0x06
	{NULL, 0, NULL},                           // 0x07
	{NULL, 0, NULL},                           // 0x08
	{NULL, 0, NULL},                           // 0x09
	{NULL, 0, NULL},                           // 0x0A
	{"DEC BC", 0, m_dec_bc},				   // 0x0B
	{"INC C", 0, m_inc_c},                     // 0x0C
	{"DEC C", 0, m_dec_c},                     // 0x0D
	{"LD C, ", 1, m_ld_c_d8},				   // 0x0E
	{NULL, 0, NULL},                           // 0x0F
	{NULL, 0, NULL},                           // 0x10
	{"LD DE, ", 2, m_ld_de_d16},			   // 0x11
	{NULL, 0, NULL},                           // 0x12
	{"INC DE", 0, m_inc_de},				   // 0x13
	{NULL, 0, NULL},                           // 0x14
	{"DEC D", 0, m_dec_d},					   // 0x15
	{"LD D, ", 1, m_ld_d_d8},				   // 0x16
	{"RLA", 0, m_rla},                         // 0x17
	{"JR ", 1, m_jr_s8},                           // 0x18
	{NULL, 0, NULL},                           // 0x19
	{"LD A, (DE)", 0, m_ld_a_de},              // 0x1A
	{NULL, 0, NULL},                           // 0x1B
	{NULL, 0, NULL},                           // 0x1C
	{"DEC E", 0, m_dec_e},					   // 0x1D
	{"LD E, ", 1, m_ld_e_d8},				    // 0x1E
	{NULL, 0, NULL},							// 0x1F
	{"JR NZ, ", 1, m_jr_nz_s8},			   // 0x20
	{"LD HL, ", 2, m_ld_hl_d16},			   // 0x21
	{"LD (HL+), A", 0, m_ld_hlplus_a},		   // 0x22
	{"INC HL", 0, m_inc_hl},				   // 0x23
	{"INC H", 0, m_inc_h},					   // 0x24
	{NULL, 0, NULL},                           // 0x25
	{NULL, 0, NULL},                           // 0x26
	{NULL, 0, NULL},                           // 0x27
	{"JR Z, ", 1, m_jr_z_s8},                // 0x28
	{NULL, 0, NULL},                           // 0x29
	{"LD A, (HL+)", 0, m_ld_a_hlplusp},		   // 0x2A
	{NULL, 0, NULL},                           // 0x2B
	{NULL, 0, NULL},                           // 0x2C
	{NULL, 0, NULL},                           // 0x2D
	{"LD L, ", 1, m_ld_l_d8},                  // 0x2E
	{NULL, 0, NULL},                           // 0x2F
	{NULL, 0, NULL},							// 0x30
	{"LD SP, ", 2, m_ld_sp_d16},			// 0x31
	{"LD (HL-), A", 0, m_ld_hlminus_a},		// 0x32
	{NULL, 0, NULL},                           // 0x33
	{NULL, 0, NULL},                           // 0x34
	{NULL, 0, NULL},                           // 0x35
	{"LD (HL), ", 1, m_ld_hlp_d8},		   // 0x36
	{NULL, 0, NULL},                           // 0x37
	{NULL, 0, NULL},                           // 0x38
	{NULL, 0, NULL},                           // 0x39
	{NULL, 0, NULL},                           // 0x3A
	{NULL, 0, NULL},                           // 0x3B
	{NULL, 0, NULL},                           // 0x3C
	{"DEC A", 0, m_dec_a},                     // 0x3D
	{"LD A, ", 1, m_ld_a_d8},				   // 0x3E
	{NULL, 0, NULL},                           // 0x3F
	{NULL, 0, NULL},                           // 0x40
	{NULL, 0, NULL},                           // 0x41
	{NULL, 0, NULL},                           // 0x42
	{NULL, 0, NULL},                           // 0x43
	{NULL, 0, NULL},                           // 0x44
	{NULL, 0, NULL},                           // 0x45
	{NULL, 0, NULL},                           // 0x46
	{NULL, 0, NULL},                           // 0x47
	{NULL, 0, NULL},                           // 0x48
	{NULL, 0, NULL},                           // 0x49
	{NULL, 0, NULL},                           // 0x4A
	{NULL, 0, NULL},                           // 0x4B
	{NULL, 0, NULL},                           // 0x4C
	{NULL, 0, NULL},                           // 0x4D
	{NULL, 0, NULL},                           // 0x4E
	{"LD C, A", 0, m_ld_c_a},                  // 0x4F
	{NULL, 0, NULL},                           // 0x50
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{"LD D, A", 0, m_ld_d_a},				   // 0x57
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x5F
	{NULL, 0, NULL},                           // 0x60
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{"LD H, A", 0, m_ld_h_a},                  // 0x67
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x6F
	{NULL, 0, NULL},                           // 0x70
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{"LD (HL), A", 0, m_ld_hl_a},              // 0x77
	{"LD A, B", 0, m_ld_a_b},				   // 0x78
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{"LD A, E", 0, m_ld_a_e},                  // 0x7B
	{"LD A, H", 0, m_ld_a_h},				   // 0x7C
	{"LD A, L", 0, m_ld_a_l},				   // 0x7D
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x7F
	{NULL, 0, NULL},                           // 0x80
	{NULL, 0, NULL},						   // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{"LD A, (HL)", 0, m_ld_a_phl},			   // 0x86
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x8F
	{"SUB B", 0, m_sub_b},					   // 0x90
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x9F
	{NULL, 0, NULL},                           // 0xA0
	{NULL, 0, NULL},                           // 0xA2
	{NULL, 0, NULL},                           // 0xA3
	{NULL, 0, NULL},                           // 0xA4
	{NULL, 0, NULL},                           // 0xA5
	{NULL, 0, NULL},                           // 0xA6
	{NULL, 0, NULL},                           // 0xA7
	{NULL, 0, NULL},                           // 0xA8
	{NULL, 0, NULL},                           // 0xA9
	{NULL, 0, NULL},                           // 0xAA
	{NULL, 0, NULL},                           // 0xAB
	{NULL, 0, NULL},                           // 0xAC
	{NULL, 0, NULL},                           // 0xAD
	{NULL, 0, NULL},							// 0xAF
	{NULL, 0, NULL},                           // 0x00
	{"XOR A", 0, m_xor_a},						// 0xAF
	{NULL, 0, NULL},                           // 0xB0
	{"OR C", 0, m_or_c},					   // 0xB1
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{"CP (HL)", 0, m_cp_hl},				   // 0xBE
	{NULL, 0, NULL},                           // 0xBF
	{NULL, 0, NULL},                           // 0xC0
	{"POP BC", 0, m_pop_bc},                   // 0xC1
	{NULL, 0, NULL},                           // 0xC2
	{"JP ", 2, m_jp_a16},				   // 0xC3
	{NULL, 0, NULL},                           // 0xC4
	{"PUSH BC", 0, m_push_bc},				   // 0xC5
	{NULL, 0, NULL},                           // 0xC6
	{NULL, 0, NULL},                           // 0xC7
	{NULL, 0, NULL},                           // 0xC8
	{"RET", 0, m_ret}, 		                   // 0xC9
	{NULL, 0, NULL},                           // 0xCA
	{"CB ", 1, m_cb_ext},						// 0xCB
	{NULL, 0, NULL},                           // 0xCC
	{"CALL ", 2, m_call},                           // 0xCD
	{NULL, 0, NULL},                           // 0xCE
	{NULL, 0, NULL},                           // 0xCF
	{NULL, 0, NULL},                           // 0xD0
	{NULL, 0, NULL},                           // 0xD1
	{NULL, 0, NULL},                           // 0xD2
	{NULL, 0, NULL},                           // 0xD3
	{NULL, 0, NULL},                           // 0xD4
	{NULL, 0, NULL},                           // 0xD5
	{NULL, 0, NULL},                           // 0xD6
	{NULL, 0, NULL},                           // 0xD7
	{NULL, 0, NULL},                           // 0xD8
	{NULL, 0, NULL},                           // 0xD9
	{NULL, 0, NULL},                           // 0xDA
	{NULL, 0, NULL},                           // 0xDB
	{NULL, 0, NULL},                           // 0xDC
	{NULL, 0, NULL},                           // 0xDD
	{NULL, 0, NULL},                           // 0xDE
	{NULL, 0, NULL},                           // 0xDF
	{"LD (a8), A -> a8: ", 1, m_ld_a8_a},	   // 0xE0
	{NULL, 0, NULL},                           // 0xE1
	{"LD (C), A", 0, m_ld_cpar_a},			   // 0xE2
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0xE9
	{"LD (a16), A -> a16: ", 2, m_ld_a16_a},			   // 0xEA
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0xEF
	{"LD A, (a8) -> a8: ", 1, m_ld_a_a8},              // 0xF0
	{NULL, 0, NULL},                           // 0xF1
	{NULL, 0, NULL},                           // 0xF2
	{"DI", 0, m_di},						   // 0xF3
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0xF9
	{NULL, 0, NULL},                           // 0xFA
	{"EI", 0, m_ei},                           // 0xFB
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{"CP ", 1, m_cp_d8},                       // 0xFE
	{NULL, 0, NULL}                            // 0xFF
};

/*
	NOP
	Opcode: 0x00
	Number of Bytes: 1
	Number of Cycles: 1

	Only advances the program counter by 1. Performs no other operations that would have an effect.
*/
void m_nop(m_dmg_t *m_dmg)
{
#ifdef OPCODE_DEBUG
	printf("\033[1;31mNOP\033[1;0m\n");
#endif

	PC += 1;
}

/*
	LD BC, d16
	Opcode: 0x01
	Number of Bytes: 3
	Number of Cycles: 3

	Load the 2 bytes of immediate data into register pair BC.
	The first byte of immediate data is the lower byte (i.e., bits 0-7),
	and the second byte of immediate data is the higher byte (i.e., bits 8-15).
*/
void m_ld_bc_d16(m_dmg_t *m_dmg, uint16_t m_d16)
{
	BC = m_d16;
	PC += 3;
}

/*
	INC B
	Opcode: 0x04
    Number of Bytes: 1
    Number of Cycles: 1

	Increment the contents of register B by 1.
*/
void m_inc_b(m_dmg_t *m_dmg)
{
	// Increment B by 1
	INC(B_REG);

	// Increment program counter by 1 (Byte)
	PC++;
}

/*
	DEC B
	Opcode: 0x05
	Number of Bytes: 1
	Number of Cycles: 1

	Decrement the contents of register B by 1.
*/
void m_dec_b(m_dmg_t *m_dmg)
{
#ifdef OPCODE_DEBUG
	printf("\033[1;31mDEC B\033[1;0m\n");
#endif
	
	// Decrement B register by 1
	DEC(B_REG);

	PC++;
}

/*
	LD B, d8
	Opcode: 0x06
	Number of Bytes: 2
	Number of Cycles: 2

	Load the 8-bit immediate operand d8 into register B.
*/
void m_ld_b_d8(m_dmg_t *m_dmg, uint8_t m_d8)
{
#ifdef OPCODE_DEBUG
	printf("\033[1;31mLD B, $%04X\033[1;0m\n", m_d8);
#endif

	B_REG = m_d8;
	PC += 2;
}

/*
	DEC BC
	Opcode: 0x0B
	Number of Bytes: 1
	Number of Cycles: 2

	Decrement the contents of register pair BC by 1.
*/
void m_dec_bc(m_dmg_t *m_dmg)
{
	BC--;
	PC++;
}

/*
	INC C
	Opcode: 0x0C
	Number of Bytes: 1
	Number of Cycles: 1

	Increment the contents of register C by 1.
*/
void m_inc_c(m_dmg_t *m_dmg)
{
#ifdef OPCODE_DEBUG
	printf("\033[1;31mINC C\033[1;0m\n");
#endif

	// Increment C by 1
	INC(C);

	PC += 1;
}

/*
	DEC C
	Opcode: 0x0D
	Number of Bytes: 1
	Number of Cycles: 1

	Increment the contents of register C by 1.
*/
void m_dec_c(m_dmg_t *m_dmg)
{
	// Decrement C register by 1
	DEC(C);

	PC++;
}

/*
	LD C, d8
	Opcode: 0x0E
	Number of Bytes: 2
	Number of Cycles: 2

	Load the 8-bit immediate operand d8 into register C.
*/
void m_ld_c_d8(m_dmg_t *m_dmg, uint8_t m_d8)
{
#ifdef OPCODE_DEBUG
	printf("\033[1;31mLD (C), $%04X\033[1;0m\n", m_d8);
#endif

	C = m_d8;
	PC += 2;
}

/*
	LD DE, d16
	Opcode: 0x11
	Number of Bytes: 3
	Number of Cycles: 3

	Load the 2 bytes of immediate data into register pair DE.

	The first byte of immediate data is the lower byte (i.e., bits 0-7),
	and the second byte of immediate data is the higher byte (i.e., bits 8-15).
*/
void m_ld_de_d16(m_dmg_t *m_dmg, uint16_t m_d16)
{
#ifdef OPCODE_DEBUG
	printf("\033[1;31mLD DE, $%04X\033[1;0m\n", m_d16);
#endif

	DE = m_d16;
	PC += 3;
}

/*
	INC DE

	Opcode: 0x13
	Number of Bytes: 1
	Number of Cycles: 2

	Increment the contents of register pair DE by 1.
*/
void m_inc_de(m_dmg_t *m_dmg)
{
#ifdef OPCODE_DEBUG
	printf("\033[1;31mINC DE\033[1;0m\n");
#endif
	DE++;
	PC++;
}

/*
	DEC D

	Opcode: 0x15
	Number of Bytes: 1
	Number of Cycles: 1
	
	Decrement the contents of register D by 1.
*/
void m_dec_d(m_dmg_t *m_dmg)
{
	// Decrement D register by 1
	DEC(D);

	PC++;
}

/*
	LD D, d8
	Opcode: 0x16
	Number of Bytes: 2
	Number of Cycles: 2
	
	Load the 8-bit immediate operand d8 into register D.
*/
void m_ld_d_d8(m_dmg_t *m_dmg, uint8_t m_d8)
{
	D = m_d8;
	PC += 2;
}

/*
	RLA
	Opcode: 0x17
	Number of Bytes: 1
	Number of Cycles: 1

	Rotate the contents of register A to the left, through the carry (CY) flag.
	That is, the contents of bit 0 are copied to bit 1, and the previous contents
	of bit 1 (before the copy operation) are copied to bit 2.
	The same operation is repeated in sequence for the rest of the register.
	The previous contents of the carry flag are copied to bit 0.
*/
void m_rla(m_dmg_t *m_dmg)
{
#ifdef OPCODE_DEBUG
	printf("\033[1;31mRLA\033[1;0m\n");
#endif

	uint8_t carry = FLAG_CHECK(CRRY) ? 1 : 0;

#ifdef PREC23
	if (A_REG & 0x40)
#else
	if (A_REG & 0b1000000)
#endif
	{
		FLAG_SET(CRRY);
	} else {
		FLAG_UNSET(CRRY);
	}

	A_REG <<= 1;
	A_REG += carry;
	
	FLAG_UNSET(NGTV);
	FLAG_UNSET(ZERO);
	FLAG_UNSET(HALF);;
	
	PC += 1;
}

/*
	JR s8
    Opcode: 0x18
    Number of Bytes: 2
    Number of Cycles: 3

	Jump s8 steps from the current address in the program counter (PC). (Jump relative.)
*/
void m_jr_s8(m_dmg_t *m_dmg, int8_t m_s8)
{
	PC += 2;
	PC += (int8_t) m_s8;
}

/*
	LD A, (DE)
	Opcode: 0x1A
	Number of Bytes: 1
	Number of Cycles: 2

	Load the 8-bit contents of memory specified by register pair DE into register A.
*/
void m_ld_a_de(m_dmg_t *m_dmg)
{
#ifdef OPCODE_DEBUG
	printf("\033[1;31mLD A, (DE)\033[1;0m\n");
#endif
	A_REG = READB(DE);
	PC += 1;
}

/*
	DEC E
	Opcode: 0x1D
	Number of Bytes: 1
	Number of Cycles: 1

	Decrement the contents of register E by 1.
*/
void m_dec_e(m_dmg_t *m_dmg)
{
	// Decrement E register by 1
	DEC(E);

	PC++;
}

/*
	LD E, d8
	Opcode: 0x1E
    Number of Bytes: 2
    Number of Cycles: 2

	Load the 8-bit immediate operand d8 into register E.
*/
void m_ld_e_d8(m_dmg_t *m_dmg, uint8_t m_d8)
{
	E = m_d8;
	PC += 2;
}

/*
	JR NZ, s8
	Opcode: 0x20
	Number of Bytes: 2
	Number of Cycles: 3/2

	If the Z flag is 0, jump s8 steps from the current address stored in the program counter (PC).
	If not, the instruction following the current JP instruction is executed (as usual).
*/
void m_jr_nz_s8(m_dmg_t *m_dmg, int8_t m_s8)
{
#ifdef OPCODE_DEBUG
	printf("\033[1;31mJR NZ, $%04hhX\033[1;0m\n", m_s8);
	printf("Operand: 0x%X\n", (uint8_t) m_s8);
#endif

	if (FLAG_CHECK(ZERO))
	{
		PC += 2;
	}
	else
	{
		// Set the PC Offset at the end of the JR NZ, s8
		PC += 2;

		// Add m_operand as an int8_t (Can go forward or backward)
		PC += (int8_t) m_s8;	
	}
}

/*
	LD HL, d16
	Opcode: 0x21
	Number of Bytes: 3
	Number of Cycles: 3

	Load the 2 bytes of immediate data into register pair HL.
	The first byte of immediate data is the lower byte (i.e., bits 0-7),
	and the second byte of immediate data is the higher byte (i.e., bits 8-15).
*/
void m_ld_hl_d16(m_dmg_t *m_dmg, uint16_t m_d16)
{
#ifdef OPCODE_DEBUG
	printf("\033[1;31mLD HL, $%04X\033[1;0m\n", m_d16);
#endif

#ifdef OPCODE_DEBUG
	printf("Address: 0x%04X\n", m_d16);
#endif

	L = (m_d16 & 0xFF);
	H = (m_d16 >> 8);

	PC += 3;
}

/*
	LD (HL+), A
	Opcode: 0x22
	Number of Bytes: 1
	Number of Cycles: 2

	Store the contents of register A into the memory location specified
	by register pair HL, and simultaneously increment the contents of HL.
*/
void m_ld_hlplus_a(m_dmg_t *m_dmg)
{
#ifdef OPCODE_DEBUG
	printf("\033[1;31mLD (HL+), A\033[1;0m\n");
#endif

	m_dmg->m_cpu->m_registers->hl++;

	WRITEB(m_dmg->m_cpu->m_registers->hl, A_REG);

	PC++;
}

/*
	INC HL
	Opcode: 0x23
	Number of Bytes: 1
	Number of Cycles: 2

	Increment the contents of register pair HL by 1.
*/
void m_inc_hl(m_dmg_t *m_dmg)
{
#ifdef OPCODE_DEBUG
	printf("\033[1;31mINC HL\033[1;0m\n");
#endif
	HL++;
	PC++;
}

/*
	INC H
	Opcode: 0x24
	Number of Bytes: 1
	Number of Cycles: 1

	Increment the contents of register H by 1.
*/
void m_inc_h(m_dmg_t *m_dmg)
{
	// Increment H by 1
	INC(H);

	PC++;
}

/*
	JR Z, s8
	Opcode: 0x28
	Number of Bytes: 2
	Number of Cycles: 3/2

	If the Z flag is 1, jump s8 steps from the current address stored in the
	program counter (PC). If not, the instruction following the current JP
	instruction is executed (as usual).
*/
void m_jr_z_s8(m_dmg_t *m_dmg, int8_t m_s8)
{
#ifdef OPCODE_DEBUG
	printf("\033[1;31mJR Z, $%04hhX\033[1;0m\n", m_s8);
	printf("Operand: 0x%X\n", (uint8_t) m_s8);
#endif

	if (FLAG_CHECK(ZERO))
	{
		// Add m_operand as an int8_t (Can go forward or backward)
		PC += (int8_t) m_s8;
	}

	PC += 2;
}

/*
	LD A, (HL+)
	Opcode: 0x2A
	Number of Bytes: 1
	Number of Cycles: 2

	Load the contents of memory specified by register pair HL into register A, and simultaneously increment the contents of HL.
*/
void m_ld_a_hlplusp(m_dmg_t *m_dmg)
{
	HL++;
	A_REG = READB(HL);
	PC++;
}

/*
	LD L, d8
	Opcode: 0x2E
	Number of Bytes: 2
	Number of Cycles: 2

	Load the 8-bit immediate operand d8 into register L.
*/
void m_ld_l_d8(m_dmg_t *m_dmg, uint8_t m_d8)
{
	L = m_d8;
	PC += 2;
}

/*
	LD SP, d16
	Opcode: 0x31
	Number of Bytes: 3
	Number of Cycles: 3

	Load the 2 bytes of immediate data into register pair SP.
	The first byte of immediate data is the lower byte (i.e., bits 0-7),
	and the second byte of immediate data is the higher byte (i.e., bits 8-15).
*/
void m_ld_sp_d16(m_dmg_t *m_dmg, uint16_t m_d16)
{

#ifdef OPCODE_DEBUG
	printf("\033[1;31mLD SP, $%04X\033[1;0m\n", m_d16);
#endif

	SP = m_d16;

#ifdef OPCODE_DEBUG
	printf("Obtained Address: 0x%X\n", m_d16);
#endif

	PC += 3;
}

/*
	LD (HL-), A
	Opcode: 0x32
	Number of Bytes: 1
	Number of Cycles: 2

	Store the contents of register A into the memory location specified
	by register pair HL, and simultaneously decrement the contents of HL.
*/
void m_ld_hlminus_a(m_dmg_t *m_dmg)
{
#ifdef OPCODE_DEBUG
	printf("\033[1;31mLD (HL-), A\033[1;0m\n");
#endif

	WRITEB(m_dmg->m_cpu->m_registers->hl, m_dmg->m_cpu->m_registers->a);
	m_dmg->m_cpu->m_registers->hl--;

	PC += 1;
}

/*
	LD (HL), d8
	Opcode: 0x36
	Number of Bytes: 2
	Number of Cycles: 3

	Store the contents of 8-bit immediate operand d8 in the memory location specified by register pair HL.
*/
void m_ld_hlp_d8(m_dmg_t *m_dmg, uint8_t m_d8)
{
	WRITEB(HL, m_d8);
	PC += 2;
}

/*
	DEC A
	Opcode: 0x3D
	Number of Bytes: 1
	Number of Cycles: 1

	Decrement the contents of register A by 
*/
void m_dec_a(m_dmg_t *m_dmg)
{
#ifdef OPCODE_DEBUG
	printf("\033[1;31mDEC A\033[1;0m\n");
#endif

	// Decrement A register by 1
	DEC(A_REG);

	PC++;
}

/*
	LD A, d8
	Opcode: 0x3E
	Number of Bytes: 2
	Number of Cycles: 2

	Load the 8-bit immediate operand d8 into register A.
*/
void m_ld_a_d8(m_dmg_t *m_dmg, uint8_t m_d8)
{
#ifdef OPCODE_DEBUG
	printf("\033[1;31mLD (A), $%04X\033[1;0m\n", m_d8);
#endif

	A_REG = m_d8;
	PC += 2;
}

/*
	LD C, A
	Opcode: 0x4F
	Number of Bytes: 1
	Number of Cycles: 1

	Load the contents of register A into register C.
*/
void m_ld_c_a(m_dmg_t *m_dmg)
{
#ifdef OPCODE_DEBUG
	printf("\033[1;31mLD C, A\033[1;0m\n");
#endif

	C = A_REG;
	PC += 1;
}


/*
	LD D, A
    Opcode: 0x57
    Number of Bytes: 1
    Number of Cycles: 1

	Load the contents of register A into register D.
*/
void m_ld_d_a(m_dmg_t *m_dmg)
{
	D = A_REG;
	PC += 1;
}

/*
	LD H, A
	Opcode: 0x67
    Number of Bytes: 1
    Number of Cycles: 1

	Load the contents of register A into register H.
*/
void m_ld_h_a(m_dmg_t *m_dmg)
{
	H = A_REG;
	PC++;
}

/*
	LD (HL), A
	Opcode: 0x77
	Number of Bytes: 1
	Number of Cycles: 2

	Store the contents of register A in the memory location specified by register pair HL.
*/
void m_ld_hl_a(m_dmg_t *m_dmg)
{
#ifdef OPCODE_DEBUG
	printf("\033[1;31mLD (HL), A\033[1;0m\n");
#endif
	WRITEB(HL, A_REG);
	PC += 1;
}

/*
	LD A, B
	Opcode: 0x78
	Number of Bytes: 1
	Number of Cycles: 2

	Load the contents of register B into register A.
*/
void m_ld_a_b(m_dmg_t *m_dmg)
{
	A_REG = B_REG;
	PC++;
}

/*
	LD A, E
	Opcode: 0x7B
	Number of Bytes: 1
	Number of Cycles: 1

	Load the contents of register E into register A.
*/
void m_ld_a_e(m_dmg_t *m_dmg)
{
#ifdef OPCODE_DEBUG
	printf("\033[1;31mLD A, E\033[1;0m\n");
#endif

	A_REG = E;
	PC++;
}

/*
	LD A, H
	Opcode: 0x7C
	Number of Bytes: 1
	Number of Cycles: 1

	Load the contents of register H into register A.
*/
void m_ld_a_h(m_dmg_t *m_dmg)
{
	A_REG = H;
	PC++;
}

/*
	LD A, L
	Opcode: 0x7D
	Number of Bytes: 1
	Number of Cycles: 1

	Load the contents of register L into register A.
*/
void m_ld_a_l(m_dmg_t *m_dmg)
{
	A_REG = L;
	PC++;
}

/*
	ADD A, (HL)
	Opcode: 0x86
	Number of Bytes: 1
	Number of Cycles: 2

	Add the contents of memory specified by register pair HL to the contents of register A, and store the results in register A.
*/
void m_ld_a_phl(m_dmg_t *m_dmg)
{
	addition(m_dmg, &A_REG, READB(HL));
	PC++;
}

/*
	SUB B
	Opcode: 0x90
	Number of Bytes: 1
	Number of Cycles: 1

	Subtract the contents of register B from the contents of
	register A, and store the results in register A.
*/
void m_sub_b(m_dmg_t *m_dmg)
{
	FLAG_SET(NGTV);
	
	if (B_REG > A_REG)
	{
		FLAG_SET(CRRY);
	} else {
		FLAG_UNSET(CRRY);
	}
	
#ifdef PREC23
	if ((B_REG & 0xF) > (A_REG & 0xF))
#else
	if ((B_REG & 0b00001111) > (A_REG & 0b00001111))
#endif
	{
		FLAG_SET(HALF);
	} else {
		FLAG_UNSET(HALF);
	}
	
	A_REG -= B_REG;
	
	if (A_REG)
	{
		FLAG_UNSET(ZERO);
	} else {
		FLAG_SET(ZERO);
	}

	PC++;
}

/*
	XOR A
	Opcode: 0xAF
	Number of Bytes: 1
	Number of Cycles: 1
	Flags: Z 0 0 0

	Take the logical exclusive-OR for each bit of the contents of register A
	and the contents of register A, and store the results in register A.
*/
void m_xor_a(m_dmg_t *m_dmg)
{
#ifdef OPCODE_DEBUG
	printf("\033[1;31mXOR A\033[1;0m\n");
#endif

	A_REG ^= A_REG;

	if (A_REG == 0)
	{
		FLAG_SET(ZERO);
	}

#ifdef OPCODE_DEBUG
			printf("Flags: 0x%02X\n", FLAGS);
#endif

	FLAG_UNSET(HALF);;
	FLAG_UNSET(CRRY);
	FLAG_UNSET(NGTV);

#ifdef OPCODE_DEBUG
			printf("Flags: 0x%02X\n", FLAGS);
#endif

	PC += 1;
}

/*
	OR C
	Opcode: 0xB1
	Number of Bytes: 1
	Number of Cycles: 1

	Take the logical OR for each bit of the contents of register C
	and the contents of register A, and store the results in register A.
*/
void m_or_c(m_dmg_t *m_dmg)
{
	or(m_dmg, C);

	PC++;
}

/*
	CP (HL)
	Opcode: 0xBE
	Number of Bytes: 1
	Number of Cycles: 2

	Compare the contents of memory specified by register pair HL and the contents of
	register A by calculating A - (HL), and set the Z flag if they are equal.

	The execution of this instruction does not affect the contents of register A.
*/
void m_cp_hl(m_dmg_t *m_dmg)
{
	FLAG_SET(NGTV);

	if (A_REG == READB(HL))
	{
		FLAG_SET(ZERO);
	} else {
		FLAG_UNSET(ZERO);
	}

	if (READB(HL) > A_REG)
	{
		FLAG_SET(CRRY);
	} else {
		FLAG_UNSET(CRRY);
	}

#ifdef PREC23
	if ((READB(HL) & 0xF) > (A_REG & 0xF))
#else
	if ((READB(HL) & 0b00001111) > (A_REG & 0b00001111))
#endif
	{
		FLAG_SET(HALF);
	} else {
		FLAG_UNSET(HALF);;
	}

	PC += 1;
}

/*
	POP BC
	Opcode: 0xC1
	Number of Bytes: 1
	Number of Cycles: 3

	Pop the contents from the memory stack into register pair into register pair BC by doing the following:

	Load the contents of memory specified by stack pointer SP into the lower portion of BC.
	Add 1 to SP and load the contents from the new memory location into the upper portion of BC.
	By the end, SP should be 2 more than its initial value.
*/
void m_pop_bc(m_dmg_t *m_dmg)
{
#ifdef OPCODE_DEBUG
	printf("\033[1;31mPOP BC\033[1;0m\n");
#endif

	uint16_t m_val = POPW();

	B_REG = m_val >> 8;
	C = m_val & 0xFF;

	PC++;
}

/*
	JP a16
    Opcode: 0xC3
    Number of Bytes: 3
    Number of Cycles: 4
	
	Load the 16-bit immediate operand a16 into the program counter (PC). a16 specifies
	the address of the subsequently executed instruction.
	The second byte of the object code (immediately following the opcode) corresponds
	to the lower-order byte of a16 (bits 0-7), and the third byte of the object code
	corresponds to the higher-order byte (bits 8-15).
*/
void m_jp_a16(m_dmg_t *m_dmg, uint16_t m_a16)
{
	PC = m_a16;
}

/*
	PUSH BC
	Opcode: 0xC5
	Number of Bytes: 1
	Number of Cycles: 4

	Push the contents of register pair BC onto the memory stack by doing the following:

	Subtract 1 from the stack pointer SP, and put the contents of the higher portion of register pair BC on the stack.
	Subtract 2 from SP, and put the lower portion of register pair BC on the stack.
	Decrement SP by 2.
*/
void m_push_bc(m_dmg_t *m_dmg)
{
#ifdef OPCODE_DEBUG
	printf("\033[1;31mPUSH BC\033[1;0m\n");
#endif

	PUSHW(BC);

	PC += 1;
}

/*
	RET
	Opcode: 0xC9
	Number of Bytes: 1
	Number of Cycles: 4

	Pop from the memory stack the program counter PC value pushed when the subroutine was called,
	returning contorl to the source program.

	The contents of the address specified by the stack pointer SP are loaded in the lower-order
	byte of PC, and the contents of SP are incremented by 1. The contents of the address specified
	by the new SP value are then loaded in the higher-order byte of PC, and the contents of SP are
	incremented by 1 again. (THe value of SP is 2 larger than before instruction execution.)
	The next instruction is fetched from the address specified by the content of PC (as usual).
*/
void m_ret(m_dmg_t *m_dmg)
{

	/*
		Once we start processing the RET opcode, what we'll do is assign the call to
		POPW (It iterates +1 on specified addr: 0xFFFA -> 0xFFFB) into a variable
		and set PC to it; after that, increase SP by 2 (0xFFFA -> 0xFFFC) to re-index the
		previous stack content. Finally, set PC to the address and add 3 as the byte offset from RET

		End of opcode diagram:
		m_addr: 0x27A3
		[0xFFFA][0xFFFB][0xFFFC]
		  0x27    0xA3    0x33
		   ^			   ^
		   |			   |
		 Old SP          New SP

	*/

	uint16_t m_addr = POPW();

#ifdef OPCODE_DEBUG
	printf("Addr: 0x%04X\n", m_addr);
#endif

	PC = m_addr + 0x3;
}

/*
	CALL a16
	Opcode: 0xCD
	Number of Bytes: 3
	Number of Cycles: 6

	In memory, push the program counter PC value corresponding to the address
	following the CALL instruction to the 2 bytes following the byte specified
	by the current stack pointer SP.
	Then load the 16-bit immediate operand a16 into PC.

	The subroutine is placed after the location specified by the new PC value.
	When the subroutine finishes, control is returned to the source program using
	a return instruction and by popping the starting address of the next instruction
	(which was just pushed) and moving it to the PC.

	With the push, the current value of SP is decremented by 1, and the higher-order
	byte of PC is loaded in the memory address specified by the new SP value.
	The value of SP is then decremented by 1 again, and the lower-order byte of PC is
	loaded in the memory address specified by that value of SP.

	The lower-order byte of a16 is placed in byte 2 of the object code,
	and the higher-order byte is placed in byte 3.
*/
void m_call(m_dmg_t *m_dmg, uint16_t m_addr)
{
#ifdef OPCODE_DEBUG
	printf("\033[1;31mCALL $%04X\033[1;0m\n", m_addr);
#endif

	/*
		Once we start processing the CALL opcode, what we'll do is
		deduct 2 from SP (0xFFFC -> 0xFFFA); call PUSWH
		(It iterates +1 on specified addr: 0xFFFA -> 0xFFFB) and set
		PC to the m_addr specified by the fetch loop.

		End of opcode diagram:
		m_addr: 0x27A3
		[0xFFFA][0xFFFB][0xFFFC]
		  0x27    0xA3    0x33
		   ^			   ^
		   |			   |
		 New SP          Old SP

	*/
	PUSHW(PC);
	
	PC = m_addr;
}

/*
	LD (a8), A
	Opcode: 0xE0
	Number of Bytes: 2
	Number of Cycles: 3

	Store the contents of register A in the internal RAM,
	port register, or mode register at the address in the range
	0xFF00-0xFFFF specified by the 8-bit immediate operand a8.

	Note: Should specify a 16-bit address in the mnemonic portion
	for a8, although the immediate operand only has the lower-order 8 bits.

	0xFF00-0xFF7F: Port/Mode registers, control register, sound register
	0xFF80-0xFFFE: Working & Stack RAM (127 bytes)
	0xFFFF: Interrupt Enable Register
*/
void m_ld_a8_a(m_dmg_t *m_dmg, uint8_t m_a8)
{
#ifdef OPCODE_DEBUG
	printf("\033[1;31mLD ($%04X), A\033[1;0m\n", m_a8);
#endif

	WRITEB((0xFF00 + m_a8), A_REG);
	PC += 2;
}

/*
	LD (C), A
	Opcode: 0xE2
	Number of Bytes: 1
	Number of Cycles: 2

	Store the contents of register A in the internal RAM, port register,
	or mode register at the address in the range 0xFF00-0xFFFF specified by register C.

	0xFF00-0xFF7F: Port/Mode registers, control register, sound register
	0xFF80-0xFFFE: Working & Stack RAM (127 bytes)
	0xFFFF: Interrupt Enable Registe
*/
void m_ld_cpar_a(m_dmg_t *m_dmg)
{
#ifdef OPCODE_DEBUG
	printf("\033[1;31mLD (C), A\033[1;0m\n");
#endif
	WRITEB((0xFF00 + C), A_REG);
	PC += 1;
}

/*
	LD (a16), A
	Opcode: 0xEA
	Number of Bytes: 3
	Number of Cycles: 4

	Store the contents of register A in the internal RAM or register specified by the 16-bit immediate operand a16.
*/
void m_ld_a16_a(m_dmg_t *m_dmg, uint16_t m_a16)
{
#ifdef OPCODE_DEBUG
	printf("\033[1;31mLD ($%04X), A\033[1;0m\n", m_a16);
#endif

	WRITEB(m_a16, A_REG);

	PC += 3;
}

/*
	LD A, (a8)
	Opcode: 0xF0
	Number of Bytes: 2
	Number of Cycles: 3
	Load into register A the contents of the internal RAM, port register, or mode register at the address in the range 0xFF00-0xFFFF specified by the 8-bit immediate operand a8.

	Note: Should specify a 16-bit address in the mnemonic portion for a8, although the immediate operand only has the lower-order 8 bits.

	0xFF00-0xFF7F: Port/Mode registers, control register, sound register
	0xFF80-0xFFFE: Working & Stack RAM (127 bytes)
	0xFFFF: Interrupt Enable Register
*/
void m_ld_a_a8(m_dmg_t *m_dmg, uint8_t m_a8)
{
	A_REG = READB(0xFF00 + m_a8);
	PC += 2;
}

/*
	DI
	Opcode: 0xF3
	Number of Bytes: 1
	Number of Cycles: 1

	Reset the interrupt master enable (IME) flag and prohibit maskable interrupts.

	Even if a DI instruction is executed in an interrupt routine, the IME flag is
	set if a return is performed with a RETI instruction.
*/
void m_di(m_dmg_t *m_dmg)
{
	interrupts.m_master = 0;
	PC++;
}

/*
	EI
	Opcode: 0xFB
	Number of Bytes: 1
	Number of Cycles: 1

	Set the interrupt master enable (IME) flag and enable maskable interrupts.
	This instruction can be used in an interrupt routine to enable higher-order interrupts.

	The IME flag is reset immediately after an interrupt occurs. The IME flag reset remains
	in effect if coontrol is returned from the interrupt routine by a RET instruction.
	However, if an EI instruction is executed in the interrupt routine, control is returned with IME = 1.
*/
void m_ei(m_dmg_t *m_dmg)
{
	interrupts.m_master = 1;
	PC++;
}

/*
	CP d8
	Opcode: 0xFE
	Number of Bytes: 2
	Number of Cycles: 2

	Compare the contents of register A and the contents of the 8-bit immediate
	operand d8 by calculating A - d8, and set the Z flag if they are equal.

	The execution of this instruction does not affect the contents of register A.
*/
void m_cp_d8(m_dmg_t *m_dmg, uint8_t m_d8)
{
#ifdef OPCODE_DEBUG
	printf("\033[1;31mCP $%02X\033[1;0m\n", m_d8);
#endif

	FLAG_SET(NGTV);

	if (A_REG == m_d8)
	{
		FLAG_SET(ZERO);
	} else {
		FLAG_UNSET(ZERO);
	}

	if (m_d8 > A_REG)
	{
		FLAG_SET(CRRY);
	} else {
		FLAG_UNSET(CRRY);
	}

#ifdef PREC23
	if ((m_d8 & 0xF) > (A_REG & 0xF))
#else
	if ((m_d8 & 0b00001111) > (A_REG & 0b00001111))
#endif
	{
		FLAG_SET(HALF);
	} else {
		FLAG_UNSET(HALF);;
	}

	PC += 2;
}
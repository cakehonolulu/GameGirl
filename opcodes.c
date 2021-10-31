#include "include/opcodes.h"

// Operand Methodology Inspired by CTurt
const struct m_sharp_lr35902_instr m_gb_instr[256] = {
	{"NOP", 0, m_nop},							// 0x00
	{NULL, 0, NULL},                           // 0x01
	{NULL, 0, NULL},                           // 0x02
	{NULL, 0, NULL},                           // 0x03
	{NULL, 0, NULL},                           // 0x04
	{NULL, 0, NULL},                           // 0x05
	{NULL, 0, NULL},                           // 0x06
	{NULL, 0, NULL},                           // 0x07
	{NULL, 0, NULL},                           // 0x08
	{NULL, 0, NULL},                           // 0x09
	{NULL, 0, NULL},                           // 0x0A
	{NULL, 0, NULL},                           // 0x0B
	{NULL, 0, NULL},                           // 0x0C
	{NULL, 0, NULL},                           // 0x0D
	{"LD C, d8", 0, m_ld_c_d8},				   // 0x0E
	{NULL, 0, NULL},                           // 0x0F
	{NULL, 0, NULL},                           // 0x10
	{NULL, 0, NULL},                           // 0x11
	{NULL, 0, NULL},                           // 0x12
	{NULL, 0, NULL},                           // 0x13
	{NULL, 0, NULL},                           // 0x14
	{NULL, 0, NULL},                           // 0x15
	{NULL, 0, NULL},                           // 0x16
	{NULL, 0, NULL},                           // 0x17
	{NULL, 0, NULL},                           // 0x18
	{NULL, 0, NULL},                           // 0x19
	{NULL, 0, NULL},                           // 0x1A
	{NULL, 0, NULL},                           // 0x1B
	{NULL, 0, NULL},                           // 0x1C
	{NULL, 0, NULL},                           // 0x1D
	{NULL, 0, NULL},							// 0x1E
	{NULL, 0, NULL},							// 0x1F
	{"JR NZ, s8", 0, m_jr_nz_s8},				// 0x20
	{"LD HL, d16", 0, m_ld_hl_d16},			// 0x21
	{NULL, 0, NULL},                           // 0x22
	{NULL, 0, NULL},                           // 0x23
	{NULL, 0, NULL},                           // 0x24
	{NULL, 0, NULL},                           // 0x25
	{NULL, 0, NULL},                           // 0x26
	{NULL, 0, NULL},                           // 0x27
	{NULL, 0, NULL},                           // 0x28
	{NULL, 0, NULL},                           // 0x29
	{NULL, 0, NULL},                           // 0x2A
	{NULL, 0, NULL},                           // 0x2B
	{NULL, 0, NULL},                           // 0x2C
	{NULL, 0, NULL},                           // 0x2D
	{NULL, 0, NULL},                           // 0x2E
	{NULL, 0, NULL},                           // 0x2F
	{NULL, 0, NULL},							// 0x30
	{"LD SP, d16", 0, m_ld_sp_d16},			// 0x31
	{"LD (HL-), A", 0, m_ld_hlminus_a},		// 0x32
	{NULL, 0, NULL},                           // 0x33
	{NULL, 0, NULL},                           // 0x34
	{NULL, 0, NULL},                           // 0x35
	{NULL, 0, NULL},                           // 0x36
	{NULL, 0, NULL},                           // 0x37
	{NULL, 0, NULL},                           // 0x38
	{NULL, 0, NULL},                           // 0x39
	{NULL, 0, NULL},                           // 0x3A
	{NULL, 0, NULL},                           // 0x3B
	{NULL, 0, NULL},                           // 0x3C
	{NULL, 0, NULL},                           // 0x3D
	{"LD A, d8", 0, m_ld_a_d8},				   // 0x3E
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
	{NULL, 0, NULL},                           // 0x4F
	{NULL, 0, NULL},                           // 0x50
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
	{NULL, 0, NULL},                           // 0x5F
	{NULL, 0, NULL},                           // 0x60
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
	{NULL, 0, NULL},                           // 0x6F
	{NULL, 0, NULL},                           // 0x70
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
	{NULL, 0, NULL},                           // 0x7F
	{NULL, 0, NULL},                           // 0x80
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
	{NULL, 0, NULL},                           // 0x8F
	{NULL, 0, NULL},                           // 0x90
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
	{NULL, 0, NULL},                           // 0xBF
	{NULL, 0, NULL},                           // 0xC0
	{NULL, 0, NULL},                           // 0xC1
	{NULL, 0, NULL},                           // 0xC2
	{NULL, 0, NULL},                           // 0xC3
	{NULL, 0, NULL},                           // 0xC4
	{NULL, 0, NULL},                           // 0xC5
	{NULL, 0, NULL},                           // 0xC6
	{NULL, 0, NULL},                           // 0xC7
	{NULL, 0, NULL},                           // 0xC8
	{NULL, 0, NULL},                           // 0xC9
	{NULL, 0, NULL},                           // 0xCA
	{"CB", 1, m_cb_ext},						// 0xCB
	{NULL, 0, NULL},                           // 0xCC
	{NULL, 0, NULL},                           // 0xCD
	{NULL, 0, NULL},                           // 0xCE
	{NULL, 0, NULL},                           // 0xCF
	{NULL, 0, NULL},                           // 0xD0
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0xD9
	{NULL, 0, NULL},                           // 0xDA
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0xDF
	{NULL, 0, NULL},						   // 0xE0
	{NULL, 0, NULL},                           // 0x00
	{"LD (C), A", 0, ld_c_a},				   // 0xE2
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0xE9
	{NULL, 0, NULL},                           // 0xEA
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0xEF
	{NULL, 0, NULL},                           // 0xF0
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0xF9
	{NULL, 0, NULL},                           // 0xFA
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL},                           // 0x00
	{NULL, 0, NULL}                            // 0x0F
};

/*
	NOP
	Opcode: 0x00
	Number of Bytes: 1
	Number of Cycles: 1

	Only advances the program counter by 1. Performs no other operations that would have an effect.
*/
void m_nop()
{
#ifdef OPCODE_DEBUG
	printf("\033[1;31mNOP\033[1;0m\n");
#endif

	m_regs.pc += 1;
}

/*
	LD C, d8

	Opcode: 0x0E
	Number of Bytes: 2
	Number of Cycles: 2

	Load the 8-bit immediate operand d8 into register C.
*/
void m_ld_c_d8()
{
	uint8_t m_operand = mmu_read_byte(mmu, (m_regs.pc + 1));
	m_regs.c = m_operand;
	m_regs.pc += 2;
}

/*
	JR NZ, s8
	Opcode: 0x20
	Number of Bytes: 2
	Number of Cycles: 3/2

	If the Z flag is 0, jump s8 steps from the current address stored in the program counter (PC).
	If not, the instruction following the current JP instruction is executed (as usual).
*/
void m_jr_nz_s8()
{
#ifdef OPCODE_DEBUG
	printf("\033[1;31mJR NZ, s8\033[1;0m\n");
#endif

	int8_t m_operand = (int8_t) mmu_read_byte(mmu, (m_regs.pc + 1));
	printf("Operand: 0x%x\n", (uint8_t) m_operand);

	uint16_t currpc = (uint16_t) m_regs.pc;

	if (!m_is_bit_set(m_regs.flags, Z))
	{
		// Set the PC Offset at the end of the JR NZ, s8
		m_regs.pc += 2;

		// Add m_operand as an int8_t (Can go forward or backward)
		m_regs.pc += (int8_t) m_operand;
	} else {
		m_regs.pc += 2;
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
void m_ld_hl_d16()
{
#ifdef OPCODE_DEBUG
	printf("\033[1;31mLD HL, d16\033[1;0m\n");
#endif
	uint16_t m_address = mmu_read_word(mmu, (m_regs.pc + 1));

#ifdef OPCODE_DEBUG
	printf("Address: 0x%04x\n", m_address);
#endif

	m_regs.l = (m_address & 0xFF);
	m_regs.h = (m_address >> 8);

	m_regs.pc += 3;
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
void m_ld_sp_d16()
{
#ifdef OPCODE_DEBUG
	printf("\033[1;31mLD SP, d16\033[1;0m\n");
#endif

	uint16_t m_addr = mmu_read_word(mmu, (m_regs.pc + 1));

	m_regs.sp = m_addr;

#ifdef OPCODE_DEBUG
	printf("Obtained Address: 0x%x\n", m_addr);
#endif

	m_regs.pc += 3;
}

/*
	LD (HL-), A
	Opcode: 0x32
	Number of Bytes: 1
	Number of Cycles: 2

	Store the contents of register A into the memory location specified
	by register pair HL, and simultaneously decrement the contents of HL.
*/
void m_ld_hlminus_a()
{
#ifdef OPCODE_DEBUG
	printf("\033[1;31mLD (HL-), A\033[1;0m\n");
#endif
	mmu_write_word(mmu, m_regs.hl, m_regs.a);
	m_regs.hl--;
	m_regs.pc += 1;
}

/*
	LD A, d8
	Opcode: 0x3E
	Number of Bytes: 2
	Number of Cycles: 2

	Load the 8-bit immediate operand d8 into register A.
*/
void m_ld_a_d8()
{
	uint8_t m_operand = mmu_read_byte(mmu, (m_regs.pc + 1));
	m_regs.a = m_operand;
	m_regs.pc += 2;
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
void m_xor_a()
{
#ifdef OPCODE_DEBUG
	printf("\033[1;31mXOR A\033[1;0m\n");
#endif

	m_regs.a ^= m_regs.a;

	if (m_regs.a == 0)
	{
		FLAG_SET(m_regs.flags, Z);
	}

#ifdef OPCODE_DEBUG
			printf("Flags: 0x%02x\n", m_regs.flags);
#endif

	FLAG_UNSET(m_regs.flags, H);
	FLAG_UNSET(m_regs.flags, C);
	FLAG_UNSET(m_regs.flags, N);

#ifdef OPCODE_DEBUG
			printf("Flags: 0x%02x\n", m_regs.flags);
#endif

	m_regs.pc += 1;
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
void ld_c_a()
{

}
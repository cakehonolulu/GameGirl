#include "include/opcodes.h"

const struct m_sharp_lr35902_instr m_gb_instr[256] = {
	{"NOP", m_nop},							// 0x00
	{NULL, NULL},                           // 0x01
	{NULL, NULL},                           // 0x02
	{NULL, NULL},                           // 0x03
	{NULL, NULL},                           // 0x04
	{NULL, NULL},                           // 0x05
	{NULL, NULL},                           // 0x06
	{NULL, NULL},                           // 0x07
	{NULL, NULL},                           // 0x08
	{NULL, NULL},                           // 0x09
	{NULL, NULL},                           // 0x0A
	{NULL, NULL},                           // 0x0B
	{NULL, NULL},                           // 0x0C
	{NULL, NULL},                           // 0x0D
	{NULL, NULL},                           // 0x0E
	{NULL, NULL},                           // 0x0F
	{NULL, NULL},                           // 0x10
	{NULL, NULL},                           // 0x11
	{NULL, NULL},                           // 0x12
	{NULL, NULL},                           // 0x13
	{NULL, NULL},                           // 0x14
	{NULL, NULL},                           // 0x15
	{NULL, NULL},                           // 0x16
	{NULL, NULL},                           // 0x17
	{NULL, NULL},                           // 0x18
	{NULL, NULL},                           // 0x19
	{NULL, NULL},                           // 0x1A
	{NULL, NULL},                           // 0x1B
	{NULL, NULL},                           // 0x1C
	{NULL, NULL},                           // 0x1D
	{NULL, NULL},							// 0x1E
	{NULL, NULL},                           // 0x1F
	{"JR NZ, s8", m_jr_nz_s8},				// 0x20
	{"LD HL, d16", m_ld_hl_d16},			// 0x21
	{NULL, NULL},                           // 0x22
	{NULL, NULL},                           // 0x23
	{NULL, NULL},                           // 0x24
	{NULL, NULL},                           // 0x25
	{NULL, NULL},                           // 0x26
	{NULL, NULL},                           // 0x27
	{NULL, NULL},                           // 0x28
	{NULL, NULL},                           // 0x29
	{NULL, NULL},                           // 0x2A
	{NULL, NULL},                           // 0x2B
	{NULL, NULL},                           // 0x2C
	{NULL, NULL},                           // 0x2D
	{NULL, NULL},                           // 0x2E
	{NULL, NULL},                           // 0x2F
	{NULL, NULL},							// 0x30
	{"LD SP, d16", m_ld_sp_d16},			// 0x31
	{"LD (HL-), A", m_ld_hlminus_a},		// 0x32
	{NULL, NULL},                           // 0x33
	{NULL, NULL},                           // 0x34
	{NULL, NULL},                           // 0x35
	{NULL, NULL},                           // 0x36
	{NULL, NULL},                           // 0x37
	{NULL, NULL},                           // 0x38
	{NULL, NULL},                           // 0x39
	{NULL, NULL},                           // 0x3A
	{NULL, NULL},                           // 0x3B
	{NULL, NULL},                           // 0x3C
	{NULL, NULL},                           // 0x3D
	{NULL, NULL},                           // 0x3E
	{NULL, NULL},                           // 0x3F
	{NULL, NULL},                           // 0x40
	{NULL, NULL},                           // 0x41
	{NULL, NULL},                           // 0x42
	{NULL, NULL},                           // 0x43
	{NULL, NULL},                           // 0x44
	{NULL, NULL},                           // 0x45
	{NULL, NULL},                           // 0x46
	{NULL, NULL},                           // 0x47
	{NULL, NULL},                           // 0x48
	{NULL, NULL},                           // 0x49
	{NULL, NULL},                           // 0x4A
	{NULL, NULL},                           // 0x4B
	{NULL, NULL},                           // 0x4C
	{NULL, NULL},                           // 0x4D
	{NULL, NULL},                           // 0x4E
	{NULL, NULL},                           // 0x4F
	{NULL, NULL},                           // 0x50
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x5F
	{NULL, NULL},                           // 0x60
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x6F
	{NULL, NULL},                           // 0x70
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x7F
	{NULL, NULL},                           // 0x80
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x8F
	{NULL, NULL},                           // 0x90
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x9F
	{NULL, NULL},                           // 0xA0
	{NULL, NULL},                           // 0xA2
	{NULL, NULL},                           // 0xA3
	{NULL, NULL},                           // 0xA4
	{NULL, NULL},                           // 0xA5
	{NULL, NULL},                           // 0xA6
	{NULL, NULL},                           // 0xA7
	{NULL, NULL},                           // 0xA8
	{NULL, NULL},                           // 0xA9
	{NULL, NULL},                           // 0xAA
	{NULL, NULL},                           // 0xAB
	{NULL, NULL},                           // 0xAC
	{NULL, NULL},                           // 0xAD
	{NULL, NULL},							// 0xAF
	{NULL, NULL},                           // 0x00
	{"XOR A", m_xor_a},						// 0xAF
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL}                           	// 0x00
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
	uint16_t m_address = mmu_read_addr16(mmu, (m_regs.pc + 1));

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

	uint16_t m_addr = mmu_read_addr16(mmu, (m_regs.pc + 1));

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
	mmu_write_addr16(mmu, m_regs.hl, m_regs.a);
	m_regs.hl--;
	m_regs.pc += 1;
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

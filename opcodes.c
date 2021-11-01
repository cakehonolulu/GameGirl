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
	{"INC C", 0, m_inc_c},                     // 0x0C
	{NULL, 0, NULL},                           // 0x0D
	{"LD C, d8", 0, m_ld_c_d8},				   // 0x0E
	{NULL, 0, NULL},                           // 0x0F
	{NULL, 0, NULL},                           // 0x10
	{"LD DE, d16", 0, m_ld_de_d16},			   // 0x11
	{NULL, 0, NULL},                           // 0x12
	{NULL, 0, NULL},                           // 0x13
	{NULL, 0, NULL},                           // 0x14
	{NULL, 0, NULL},                           // 0x15
	{NULL, 0, NULL},                           // 0x16
	{NULL, 0, NULL},                           // 0x17
	{NULL, 0, NULL},                           // 0x18
	{NULL, 0, NULL},                           // 0x19
	{"LD A, (DE)", 0, m_ld_a_de},              // 0x1A
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
	{"LD C, A", 0, m_ld_c_a},                  // 0x4F
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
	{"LD (HL), A", 0, m_ld_hl_a},              // 0x77
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
	{"CALL", 0, m_call},                           // 0xCD
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
	{"LD (a8), A", 0, m_ld_a8_a},			   // 0xE0
	{NULL, 0, NULL},                           // 0xE1
	{"LD (C), A", 0, m_ld_cpar_a},			   // 0xE2
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

	PC += 1;
}

/*
	INC C
	Opcode: 0x0C
	Number of Bytes: 1
	Number of Cycles: 1

	Increment the contents of register C by 1.
*/
void m_inc_c()
{
#ifdef OPCODE_DEBUG
	printf("\033[1;31mINC C\033[1;0m\n");
#endif

	if ((C & 0x0f) == 0x0f)
	{
		FLAG_SET(H);
	} else {
		FLAG_UNSET(H);
	}

	C++;
	
	if (C)
	{
		FLAG_UNSET(Z);
	} else {
		FLAG_SET(Z);
	}

	FLAG_UNSET(N);

	PC += 1;
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
	uint8_t m_operand = mmu_read_byte(mmu, (PC + 1));

#ifdef OPCODE_DEBUG
	printf("\033[1;31mLD (C), $%04X\033[1;0m\n", m_operand);
#endif

	C = m_operand;
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
void m_ld_de_d16()
{
	uint16_t m_operand = mmu_read_word(mmu, PC + 1);

#ifdef OPCODE_DEBUG
	printf("\033[1;31mLD DE, $%04X\033[1;0m\n", m_operand);
#endif

	DE = m_operand;
	PC += 3;
}

/*
	LD A, (DE)
	Opcode: 0x1A
	Number of Bytes: 1
	Number of Cycles: 2

	Load the 8-bit contents of memory specified by register pair DE into register A.
*/
void m_ld_a_de()
{
#ifdef OPCODE_DEBUG
	printf("\033[1;31mLD A, (DE)\033[1;0m\n");
#endif
	A = mmu_read_byte(mmu, DE);
	PC += 1;
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
	int8_t m_operand = (int8_t) mmu_read_byte(mmu, (PC + 1));

#ifdef OPCODE_DEBUG
	printf("\033[1;31mJR NZ, $%04hhX\033[1;0m\n", m_operand);
#endif

	printf("Operand: 0x%X\n", (uint8_t) m_operand);

	uint16_t currpc = (uint16_t) PC;

	if (!m_is_bit_set(FLAGS, Z))
	{
		// Set the PC Offset at the end of the JR NZ, s8
		PC += 2;

		// Add m_operand as an int8_t (Can go forward or backward)
		PC += (int8_t) m_operand;
	} else {
		PC += 2;
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
	uint16_t m_address = mmu_read_word(mmu, (PC + 1));

#ifdef OPCODE_DEBUG
	printf("\033[1;31mLD HL, $%04X\033[1;0m\n", m_address);
#endif

#ifdef OPCODE_DEBUG
	printf("Address: 0x%04X\n", m_address);
#endif

	L = (m_address & 0xFF);
	H = (m_address >> 8);

	PC += 3;
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
	uint16_t m_addr = mmu_read_word(mmu, (PC + 1));

#ifdef OPCODE_DEBUG
	printf("\033[1;31mLD SP, $%04X\033[1;0m\n", m_addr);
#endif

	SP = m_addr;

#ifdef OPCODE_DEBUG
	printf("Obtained Address: 0x%X\n", m_addr);
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
void m_ld_hlminus_a()
{
#ifdef OPCODE_DEBUG
	printf("\033[1;31mLD (HL-), A\033[1;0m\n");
#endif
	mmu_write_word(mmu, Hl, A);
	Hl--;
	PC += 1;
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
	uint8_t m_operand = mmu_read_byte(mmu, (PC + 1));

#ifdef OPCODE_DEBUG
	printf("\033[1;31mLD (A), $%04X\033[1;0m\n", m_operand);
#endif

	A = m_operand;
	PC += 2;
}

/*
	LD C, A
	Opcode: 0x4F
	Number of Bytes: 1
	Number of Cycles: 1

	Load the contents of register A into register C.
*/
void m_ld_c_a()
{
#ifdef OPCODE_DEBUG
	printf("\033[1;31mLD C, A\033[1;0m\n");
#endif

	C = A;
	PC += 1;
}

/*
	LD (HL), A
	Opcode: 0x77
	Number of Bytes: 1
	Number of Cycles: 2

	Store the contents of register A in the memory location specified by register pair HL.
*/
void m_ld_hl_a()
{
#ifdef OPCODE_DEBUG
	printf("\033[1;31mLD (HL), A\033[1;0m\n");
#endif
	mmu_write_byte(Hl, A);
	PC += 1;
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

	A ^= A;

	if (A == 0)
	{
		FLAG_SET(Z);
	}

#ifdef OPCODE_DEBUG
			printf("Flags: 0x%02X\n", FLAGS);
#endif

	FLAG_UNSET(H);
	FLAG_UNSET(C);
	FLAG_UNSET(N);

#ifdef OPCODE_DEBUG
			printf("Flags: 0x%02X\n", FLAGS);
#endif

	PC += 1;
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
void m_call()
{
	uint16_t m_addr = mmu_read_word(mmu, PC + 1);

#ifdef OPCODE_DEBUG
	printf("\033[1;31mCALL $%04X\033[1;0m\n", m_addr);
#endif

	SP -= 2;
	
	mmu_write_word(SP, (uint8_t) (PC & 0x00ff));
	
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
void m_ld_a8_a()
{
	uint8_t m_operand = mmu_read_byte(mmu, PC + 1);

#ifdef OPCODE_DEBUG
	printf("\033[1;31mLD ($%04X), A\033[1;0m\n", m_operand);
#endif

	mmu_write_byte((0xFF00 + m_operand), A);
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
void m_ld_cpar_a()
{
#ifdef OPCODE_DEBUG
	printf("\033[1;31mLD (C), A\033[1;0m\n");
#endif
	mmu_write_byte((0xFF00 + C), A);
	PC += 1;
}
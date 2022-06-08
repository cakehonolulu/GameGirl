#include <cb_opcodes.h>

const struct m_sharp_lr35902_instr_cb m_gb_instr_cb[256] = {
	{NULL, NULL},							// 0x00
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
	{"RL C", m_rl_c},                       // 0x11
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
	{NULL, NULL},                           // 0x20
	{NULL, NULL},                           // 0x21
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x2A
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x30
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{"SWAP A", m_swap_a},					// 0x37
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
	{"BIT 7, H", m_bit_7_h},				// 0x7C
	{NULL, NULL},                           // 0x00
	{NULL, NULL},                           // 0x00
	{NULL, NULL},							// 0x7C
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

void m_cb_ext(m_dmg_t *m_dmg, uint8_t cb_instr)
{
#ifdef OPCODE_DEBUG
	printf("CB Mode Instr!\n");

	printf("Current CB Opcode: 0x%02X\n", cb_instr);
#endif

	if (m_gb_instr_cb[cb_instr].m_funct == NULL)
	{
		printf("Unimplemented Opcode: 0xCB%02X\n", cb_instr);
		m_printregs(m_dmg);
		exit(EXIT_FAILURE);
	} else {
		((void (*)(m_dmg_t *m_dmg))m_gb_instr_cb[cb_instr].m_funct)(m_dmg);
	}
}

/*
	RL C
	Opcode: 0xCB11
	Number of Bytes: 2
	Number of Cycles: 2

	Rotate the contents of register C to the left.
	That is, the contents of bit 0 are copied to bit 1, and
	the previous contents of bit 1 (before the copy operation)
	are copied to bit 2. The same operation is repeated in sequence
	for the rest of the register. The previous contents of the carry
	(CY) flag are copied to bit 0 of register C.
*/
void m_rl_c(m_dmg_t *m_dmg)
{
#ifdef OPCODE_DEBUG
	printf("\033[1;31mRL C\033[1;0m\n");
#endif

	uint8_t oldcarry = FLAG_CHECK(CRRY) ? 1 : 0;

	if ((C >> 7) & 1)
	{
		FLAG_SET(CRRY);
	} else {
		FLAG_UNSET(CRRY);
	}

	C = (C << 1) | oldcarry;

	if (C)
	{
		FLAG_UNSET(ZERO);
	} else {
		FLAG_SET(ZERO);
	}

	FLAG_UNSET(NGTV);
	FLAG_UNSET(HALF);
	
	PC += 2;
}

/*
	SWAP A
    Opcode: 0xCB37
    Number of Bytes: 2
    Number of Cycles: 2
    Flags: Z 0 0 0

	Shift the contents of the lower-order four bits (0-3) of register A to the higher-order four
	bits (4-7) of the register, and shift the higher-order four bits to the lower-order four bits.
*/
void m_swap_a(m_dmg_t *m_dmg)
{
	A_REG = ((A_REG & 0xf) << 4) | ((A_REG & 0xf0) >> 4);
	
	if (A_REG)
	{
		FLAG_UNSET(ZERO);
	}
	else
	{
		FLAG_SET(ZERO);
	}

	FLAG_UNSET(NGTV);
	FLAG_UNSET(HALF);
	FLAG_UNSET(CRRY);

	PC += 2;
}

/*
	BIT 7, H
	Opcode: 0xCB7C
	Number of Bytes: 2
	Number of Cycles: 2

	Copy the complement of the contents of bit 7 in register H
	to the Z flag of the program status word (PSW).
*/
void m_bit_7_h(m_dmg_t *m_dmg)
{
	if (BIT_CHECK(H, 7))
	{
		FLAG_UNSET(ZERO);
	} else {
		FLAG_SET(ZERO);
	}

	FLAG_UNSET(NGTV);

	FLAG_SET(HALF);

#ifdef OPCODE_DEBUG
	printf("Flags: 0x%02X\n", FLAGS);
#endif
	PC += 2;
}

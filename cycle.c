#include "include/cycle.h"
#include "include/opcodes.h"

void m_init_registers()
{
	A = 0;
	B = 0;

	C = 0;
	D = 0;

	E = 0;
	F = 0;

	L = 0;
	H = 0;

	PC = 0;
	SP = 0;

	FLAGS = 0;
}

uint8_t m_fetch()
{
	return (uint8_t) mmu_read_byte(PC);
}

uint8_t m_fetchopbyte()
{
	return (uint8_t) mmu_read_byte(PC + 1);
}

uint16_t m_fetchopword()
{
	uint8_t m_rb = mmu_read_byte(PC + 1);

	uint8_t m_lb = mmu_read_byte(PC + 2);

	uint16_t m_w = (((m_lb & 0xFF) << 8) | (m_rb & 0xFF));

	return (uint16_t) m_w;
}

bool m_is_bit_set(uint8_t m_register, size_t m_bit)
{
	return 1 == ((m_register >> m_bit) & 1);
}

uint8_t m_opcode;
uint8_t m_boperand;
uint16_t m_woperand;

void m_exec()
{
	m_opcode = m_fetch();

#ifdef OPCODE_DEBUG
	printf("Current opcode: 0x%02X\n", m_opcode);
#endif

	m_boperand = 0;
	m_woperand = 0;

	if (m_gb_instr[m_opcode].m_operand == 1)
	{
		m_boperand = m_fetchopbyte();
	} else if (m_gb_instr[m_opcode].m_operand == 2) {
		m_woperand = m_fetchopword();
	}

	switch(m_gb_instr[m_opcode].m_operand)
	{
		case 0:
			if (m_gb_instr[m_opcode].m_funct == NULL)
			{
				printf("Unimplemented Opcode 0x%02X\n", m_opcode);
				m_printregs();
				exit(EXIT_FAILURE);
			} else {
				((void (*)(void))m_gb_instr[m_opcode].m_funct)();
			}
			break;
		
		case 1:
			if (m_gb_instr[m_opcode].m_funct == NULL)
			{
				printf("Unimplemented Opcode 0x%02X\n", m_opcode);
				m_printregs();
				exit(EXIT_FAILURE);
			} else {
				if ((m_opcode == 0x18) | (m_opcode == 0x20) | (m_opcode == 0x28))
				{
					((void (*)(uint8_t))m_gb_instr[m_opcode].m_funct)((int8_t) m_boperand);
				} else {
					((void (*)(uint8_t))m_gb_instr[m_opcode].m_funct)((uint8_t) m_boperand);
				}
			}
			break;

		case 2:
			if (m_gb_instr[m_opcode].m_funct == NULL)
			{
				printf("Unimplemented Opcode 0x%02X\n", m_opcode);
				m_printregs();
				exit(EXIT_FAILURE);
			} else {
				((void (*)(uint16_t))m_gb_instr[m_opcode].m_funct)((uint16_t) m_woperand);
			}
			break;

		default:
			break;
	}

	
}

void m_printregs()
{
	printf("\n\033[1;31mGeneral-Purpose Registers:\033[0m\n");
	printf("\033[0;35mA:\033[0m 0x%02X, \033[0;35mF:\033[0m 0x%02X; \033[0;35mAF:\033[0m 0x%04X\n", A, F, AF);
	printf("\033[0;35mB:\033[0m 0x%02X, \033[0;35mC:\033[0m 0x%02X; \033[0;35mBC:\033[0m 0x%04X\n", B, C, BC);
	printf("\033[0;35mD:\033[0m 0x%02X, \033[0;35mE:\033[0m 0x%02X; \033[0;35mDE:\033[0m 0x%04X\n", D, E, DE);
	printf("\033[0;35mH:\033[0m 0x%02X, \033[0;35mL:\033[0m 0x%02X; \033[0;35mHL:\033[0m 0x%04X\n\n", H, L, HL);

	printf("\033[1;33mSegment Registers:\033[0:0m\n");
	printf("\033[1;35mSP:\033[0m 0x%04X\n\n", SP);

	printf("\033[1;32mProgram Flow Registers:\033[0:0m\n");
	printf("\033[1;35mPC:\033[0m 0x%04X\n\n", PC);

	printf("\033[1;34mFLAGS:\033[0:0m\n");

	printf("\033[1;35mZ: ");

	if (m_is_bit_set(FLAGS, ZERO))
	{
		printf("\033[0m1   ");
	} else {
		printf("\033[0m0   ");
	}

	printf("\033[1;35mN: ");

	if (m_is_bit_set(FLAGS, NGTV))
	{
		printf("\033[0m1   \n");
	} else {
		printf("\033[0m0   \n");
	}

	printf("\033[1;35mH: ");

	if (m_is_bit_set(FLAGS, HALF))
	{
		printf("\033[0m1   ");
	} else {
		printf("\033[0m0   ");
	}

	printf("\033[1;35mC: ");

	if (m_is_bit_set(FLAGS, CRRY))
	{
		printf("\033[0m1   \n");
	} else {
		printf("\033[0m0   \n\n");
	}
}

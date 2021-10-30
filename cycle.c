#include "include/cycle.h"
#include "include/opcodes.h"

void m_init_registers(gb_registers_t *m_regs)
{
	m_regs->a = 0;
	m_regs->b = 0;

	m_regs->c = 0;
	m_regs->d = 0;

	m_regs->e = 0;
	m_regs->f = 0;

	m_regs->l = 0;
	m_regs->h = 0;

	m_regs->pc = 0;
	m_regs->sp = 0;

	m_regs->flags = 0;
}

uint8_t m_fetch(gb_mmu_t *gb_mmu, gb_registers_t *m_regs)
{
	uint8_t m_opcode = mmu_read_addr8(gb_mmu, m_regs->pc);
	return m_opcode;
}

uint8_t m_fetchop(gb_mmu_t *gb_mmu, gb_registers_t *m_regs)
{
	uint8_t m_opcodeop = mmu_read_addr8(gb_mmu, (m_regs->pc + 1));
	return m_opcodeop;
}

bool m_is_bit_set(uint8_t m_register, size_t m_bit)
{
	return 1 == ((m_register >> m_bit) & 1);
}

void m_exec(gb_mmu_t *gb_mmu, gb_registers_t *m_regs)
{
	uint8_t m_opcode = m_fetch(gb_mmu, m_regs);

	printf("Current opcode: 0x%x\n", m_opcode);

	uint8_t m_operand = 0;

	if (m_gb_instr[m_opcode].m_operand == 1)
	{
		m_operand = m_fetchop(gb_mmu, m_regs);
		printf("Operand: 0x%x\n", m_operand);
	}

	switch(m_gb_instr[m_opcode].m_operand)
	{
		case 0:
			((void (*)(void))m_gb_instr[m_opcode].m_funct)();
			break;
		
		case 1:
			((void (*)(uint8_t))m_gb_instr[m_opcode].m_funct)((uint8_t) m_operand);
			break;

		default:
			break;
	}

	
}

void m_printregs(gb_registers_t *m_regs)
{
	printf("\n\033[1;31mGeneral-Prupose Registers:\033[0m\n");
	printf("\033[0;35mA:\033[0m 0x%02x, \033[0;35mF:\033[0m 0x%02x; \033[0;35mAF:\033[0m 0x%04x\n", m_regs->a, m_regs->f, m_regs->af);
	printf("\033[0;35mB:\033[0m 0x%02x, \033[0;35mC:\033[0m 0x%02x; \033[0;35mBC:\033[0m 0x%04x\n", m_regs->b, m_regs->c, m_regs->bc);
	printf("\033[0;35mD:\033[0m 0x%02x, \033[0;35mE:\033[0m 0x%02x; \033[0;35mDE:\033[0m 0x%04x\n", m_regs->d, m_regs->e, m_regs->de);
	printf("\033[0;35mH:\033[0m 0x%02x, \033[0;35mL:\033[0m 0x%02x; \033[0;35mHL:\033[0m 0x%04x\n\n", m_regs->h, m_regs->l, m_regs->hl);

	printf("\033[1;33mSegment Registers:\033[0:0m\n");
	printf("\033[1;35mSP:\033[0m 0x%04x\n\n", m_regs->sp);

	printf("\033[1;32mProgram Flow Registers:\033[0:0m\n");
	printf("\033[1;35mPC:\033[0m 0x%04x\n\n", m_regs->pc);

	printf("\033[1;34mFlags:\033[0:0m\n");

	printf("\033[1;35mZ: ");

	if (m_is_bit_set(m_regs->flags, Z))
	{
		printf("\033[0m1   ");
	} else {
		printf("\033[0m0   ");
	}

	printf("\033[1;35mN: ");

	if (m_is_bit_set(m_regs->flags, N))
	{
		printf("\033[0m1   \n");
	} else {
		printf("\033[0m0   \n");
	}

	printf("\033[1;35mH: ");

	if (m_is_bit_set(m_regs->flags, H))
	{
		printf("\033[0m1   ");
	} else {
		printf("\033[0m0   ");
	}

	printf("\033[1;35mC: ");

	if (m_is_bit_set(m_regs->flags, C))
	{
		printf("\033[0m1   \n");
	} else {
		printf("\033[0m0   \n\n");
	}
}

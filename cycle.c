#include "include/cycle.h"

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
}

uint8_t m_fetch(gb_mmu_t *gb_mmu, gb_registers_t *m_regs)
{
	uint8_t m_opcode = mmu_read_addr8(gb_mmu, m_regs->pc);
	return m_opcode;
}

void m_exec(gb_mmu_t *gb_mmu, gb_registers_t *m_regs)
{
	uint8_t m_opcode = m_fetch(gb_mmu, m_regs);

	printf("Current opcode: 0x%x\n", m_opcode);

	switch (m_opcode)
	{
		/*
			LD SP, d16
			Number of Bytes: 3
			Number of Cycles: 3

			Load the 2 bytes of immediate data into register pair SP.
			The first byte of immediate data is the lower byte (i.e., bits 0-7),
			and the second byte of immediate data is the higher byte (i.e., bits 8-15).
		*/
		case 0x31:
#ifdef OPCODE_DEBUG
			printf("LD SP, d16\n");
#endif
			uint16_t m_addr = mmu_read_addr16(gb_mmu, (m_regs->pc + 1));

			m_regs->sp = m_addr;

#ifdef OPCODE_DEBUG
			printf("Obtained Address: 0x%x\n", m_addr);
#endif
			m_regs->pc += 3;

			break;

		default:
			printf("Unimplemented Opcode: 0x%x!\n", m_opcode);
			m_printregs(m_regs);
			m_regs->isUnimplemented = true;
			break;
	}
	
}

void m_printregs(gb_registers_t *m_regs)
{
	printf("\n\033[1;31mGeneral-Prupose Registers:\033[0m\n");
	printf("\033[1;34mA:\033[0m 0x%02x, \033[1;31mF:\033[0m 0x%02x; \033[1;35mAF:\033[0m 0x%04x\n", m_regs->a, m_regs->f, m_regs->af);
	printf("\033[1;34mB:\033[0m 0x%02x, \033[1;31mC:\033[0m 0x%02x; \033[1;35mBC:\033[0m 0x%04x\n", m_regs->b, m_regs->c, m_regs->bc);
	printf("\033[1;34mD:\033[0m 0x%02x, \033[1;31mE:\033[0m 0x%02x; \033[1;35mDE:\033[0m 0x%04x\n", m_regs->d, m_regs->e, m_regs->de);
	printf("\033[1;34mH:\033[0m 0x%02x, \033[1;31mL:\033[0m 0x%02x; \033[1;35mHL:\033[0m 0x%04x\n\n", m_regs->h, m_regs->l, m_regs->hl);

	printf("\033[1;33mSegment Registers:\033[0:0m\n");
	printf("\033[1;34mSP:\033[0m 0x%04x\n\n", m_regs->sp);

	printf("\033[1;32mProgram Flow Registers:\033[0:0m\n");
	printf("\033[1;34mPC:\033[0m 0x%04x\n\n", m_regs->pc);
}
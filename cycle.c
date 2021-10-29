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

	switch (m_opcode & 0xFF00)
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

#ifdef OPCODE_DEBUG
			printf("Obtained Address: 0x%x\n", m_addr);
#endif

			break;

		default:
			printf("Unimplemented Opcode: 0x%x!\n", m_opcode);
			m_regs->isUnimplemented = true;
			break;
	}
	

}

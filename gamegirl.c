#include "includes/gamegirl.h"
#include "includes/mmu.h"

int main(int argc, char **argv)
{
	printf("GameGirl - A C-21 Multiplatform Game Boy Emulator\n");

	// Init MMU
	gb_mmu_t *mmu = mmu_init();

	// Load Bootrom
	m_load_bootrom(mmu);

	// Declare the Registers
	gb_registers_t m_regs;

	// Initialize Registers
	m_init_registers(&m_regs);

	// Start fetching & executing instructions
	m_exec(mmu, &m_regs);

	// Free MMU data
	mmu_halt(mmu);

	return EXIT_SUCCESS;
}

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
	printf("Opcode: 0x%x\n", m_opcode);
}


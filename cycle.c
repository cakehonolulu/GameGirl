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

	m_regs->flags = 0;
}

uint8_t m_fetch(gb_mmu_t *gb_mmu, gb_registers_t *m_regs)
{
	uint8_t m_opcode = mmu_read_addr8(gb_mmu, m_regs->pc);
	return m_opcode;
}

bool m_is_bit_set(uint8_t m_register, size_t m_bit)
{
	return 1 == ((m_register >> m_bit) & 1);
}

void m_exec(gb_mmu_t *gb_mmu, gb_registers_t *m_regs)
{
	uint8_t m_opcode = m_fetch(gb_mmu, m_regs);

	printf("Current opcode: 0x%x\n", m_opcode);

	switch (m_opcode)
	{
		/*
			NOP
			Opcode: 0x00
			Number of Bytes: 1
			Number of Cycles: 1

			Only advances the program counter by 1. Performs no other operations that would have an effect.
		*/
		case 0x0:
			m_regs->pc += 1;
			break;
		/*
			LD HL, d16
			Opcode: 0x21
			Number of Bytes: 3
			Number of Cycles: 3

			Load the 2 bytes of immediate data into register pair HL.
			The first byte of immediate data is the lower byte (i.e., bits 0-7),
			and the second byte of immediate data is the higher byte (i.e., bits 8-15).
		*/
		case 0x21:
			uint16_t m_address = mmu_read_addr16(gb_mmu, (m_regs->pc + 1));

#ifdef OPCODE_DEBUG
			printf("Address: 0x%04x\n", m_address);
#endif

			m_regs->l = (m_address & 0xFF);
			m_regs->h = (m_address >> 8);

			m_regs->pc += 3;
			break;

		/*
			LD SP, d16
			Opcode: 0x31
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

		/*
			LD (HL-), A
			Opcode: 0x32
			Number of Bytes: 1
			Number of Cycles: 2

			Store the contents of register A into the memory location specified
			by register pair HL, and simultaneously decrement the contents of HL.
		*/
		case 0x32:
			mmu_write_addr16(gb_mmu, m_regs->hl, m_regs->a);
			m_regs->hl--;
			m_regs->pc += 1;
			break;

		/*
			XOR A
			Opcode: 0xAF
			Number of Bytes: 1
			Number of Cycles: 1
			Flags: Z 0 0 0

			Take the logical exclusive-OR for each bit of the contents of register A
			and the contents of register A, and store the results in register A.
		*/
		case 0xAF:
			m_regs->a ^= m_regs->a;

			if (m_regs->a == 0)
			{
				FLAG_SET(Z);
			}

#ifdef OPCODE_DEBUG
			printf("Flags: 0x%02x\n", m_regs->flags);
#endif
			FLAG_UNSET(H);
			FLAG_UNSET(C);
			FLAG_UNSET(N);
#ifdef OPCODE_DEBUG
			printf("Flags: 0x%02x\n", m_regs->flags);
#endif
			m_regs->pc += 1;
			break;

		case 0xCB:
			uint8_t m_cbvariant = mmu_read_addr8(gb_mmu, m_regs->pc + 1);

			switch (m_cbvariant)
			{
				/*
					BIT 7, H
					Opcode: 0xCB7C
					Number of Bytes: 2
					Number of Cycles: 2

					Copy the complement of the contents of bit 7 in register H
					to the Z flag of the program status word (PSW).
				*/
				case 0x7C:
					if (!m_is_bit_set(m_regs->h, Z))
					{
						FLAG_SET(Z);
					} else {
						FLAG_UNSET(Z);
					}

					FLAG_UNSET(N);

					FLAG_SET(H);
#ifdef OPCODE_DEBUG
					printf("Flags: 0x%02x\n", m_regs->flags);
#endif
					m_regs->pc += 2;
					break;

				default:
					break;
			}

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

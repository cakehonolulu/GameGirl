#include <cycle.h>
#include <opcodes.h>
#include <ppu.h>
#include <interrupts.h>

const uint8_t m_ticks_by_opcode[256] = {
	2, 6, 4, 4, 2, 2, 4, 4, 10, 4, 4, 4, 2, 2, 4, 4, // 0x0_
	2, 6, 4, 4, 2, 2, 4, 4,  4, 4, 4, 4, 2, 2, 4, 4, // 0x1_
	0, 6, 4, 4, 2, 2, 4, 2,  0, 4, 4, 4, 2, 2, 4, 2, // 0x2_
	4, 6, 4, 4, 6, 6, 6, 2,  0, 4, 4, 4, 2, 2, 4, 2, // 0x3_
	2, 2, 2, 2, 2, 2, 4, 2,  2, 2, 2, 2, 2, 2, 4, 2, // 0x4_
	2, 2, 2, 2, 2, 2, 4, 2,  2, 2, 2, 2, 2, 2, 4, 2, // 0x5_
	2, 2, 2, 2, 2, 2, 4, 2,  2, 2, 2, 2, 2, 2, 4, 2, // 0x6_
	4, 4, 4, 4, 4, 4, 2, 4,  2, 2, 2, 2, 2, 2, 4, 2, // 0x7_
	2, 2, 2, 2, 2, 2, 4, 2,  2, 2, 2, 2, 2, 2, 4, 2, // 0x8_
	2, 2, 2, 2, 2, 2, 4, 2,  2, 2, 2, 2, 2, 2, 4, 2, // 0x9_
	2, 2, 2, 2, 2, 2, 4, 2,  2, 2, 2, 2, 2, 2, 4, 2, // 0xa_
	2, 2, 2, 2, 2, 2, 4, 2,  2, 2, 2, 2, 2, 2, 4, 2, // 0xb_
	0, 6, 0, 6, 0, 8, 4, 8,  0, 2, 0, 0, 0, 6, 4, 8, // 0xc_
	0, 6, 0, 0, 0, 8, 4, 8,  0, 8, 0, 0, 0, 0, 4, 8, // 0xd_
	6, 6, 4, 0, 0, 8, 4, 8,  8, 2, 8, 0, 0, 0, 4, 8, // 0xe_
	6, 6, 4, 2, 0, 8, 4, 8,  6, 4, 8, 2, 0, 0, 4, 8  // 0xf_
};

const uint8_t m_ticks_by_cbopcode[256] = {
	8, 8, 8, 8, 8,  8, 16, 8,  8, 8, 8, 8, 8, 8, 16, 8, // 0x0_
	8, 8, 8, 8, 8,  8, 16, 8,  8, 8, 8, 8, 8, 8, 16, 8, // 0x1_
	8, 8, 8, 8, 8,  8, 16, 8,  8, 8, 8, 8, 8, 8, 16, 8, // 0x2_
	8, 8, 8, 8, 8,  8, 16, 8,  8, 8, 8, 8, 8, 8, 16, 8, // 0x3_
	8, 8, 8, 8, 8,  8, 12, 8,  8, 8, 8, 8, 8, 8, 12, 8, // 0x4_
	8, 8, 8, 8, 8,  8, 12, 8,  8, 8, 8, 8, 8, 8, 12, 8, // 0x5_
	8, 8, 8, 8, 8,  8, 12, 8,  8, 8, 8, 8, 8, 8, 12, 8, // 0x6_
	8, 8, 8, 8, 8,  8, 12, 8,  8, 8, 8, 8, 8, 8, 12, 8, // 0x7_
	8, 8, 8, 8, 8,  8, 12, 8,  8, 8, 8, 8, 8, 8, 12, 8, // 0x8_
	8, 8, 8, 8, 8,  8, 12, 8,  8, 8, 8, 8, 8, 8, 12, 8, // 0x9_
	8, 8, 8, 8, 8,  8, 12, 8,  8, 8, 8, 8, 8, 8, 12, 8, // 0xa_
	8, 8, 8, 8, 8,  8, 12, 8,  8, 8, 8, 8, 8, 8, 12, 8, // 0xb_
	8, 8, 8, 8, 8,  8, 12, 8,  8, 8, 8, 8, 8, 8, 12, 8, // 0xc_
	8, 8, 8, 8, 8,  8, 12, 8,  8, 8, 8, 8, 8, 8, 12, 8, // 0xd_
	8, 8, 8, 8, 8,  8, 12, 8,  8, 8, 8, 8, 8, 8, 12, 8, // 0xe_
	8, 8, 8, 8, 8,  8, 12, 8,  8, 8, 8, 8, 8, 8, 12, 8  // 0xf_
};

void m_init_registers(m_dmg_t *m_dmg)
{
	m_dmg->m_cpu = (m_dmg_cpu*) malloc(sizeof(m_dmg_cpu));
	m_dmg->m_cpu->m_registers = (gb_registers_t*) malloc(sizeof(gb_registers_t));
	m_dmg->m_cpu->interrupts = (m_interrupts*) malloc(sizeof(m_interrupts));

	// If BootROM isn't loaded, bootstrap manually into cart area
	if (!m_dmg->m_memory->m_in_bootrom)
	{
		PC = 0x100;
		m_af_reg_set(m_dmg, 0x01B0);
		BC = 0x0013;
		DE = 0x00D8;
		HL = 0x014D;
		SP = 0xFFFE;

		WRITEB(0xFF05, 0);
		WRITEB(0xFF06, 0);
		WRITEB(0xFF07, 0);
		WRITEB(0xFF10, 0x80);
		WRITEB(0xFF11, 0xBF);
		WRITEB(0xFF12, 0xF3);
		WRITEB(0xFF14, 0xBF);
		WRITEB(0xFF16, 0x3F);
		WRITEB(0xFF17, 0x00);
		WRITEB(0xFF19, 0xBF);
		WRITEB(0xFF1A, 0x7A);
		WRITEB(0xFF1B, 0xFF);
		WRITEB(0xFF1C, 0x9F);
		WRITEB(0xFF1E, 0xBF);
		WRITEB(0xFF20, 0xFF);
		WRITEB(0xFF21, 0x00);
		WRITEB(0xFF22, 0x00);
		WRITEB(0xFF23, 0xBF);
		WRITEB(0xFF24, 0x77);
		WRITEB(0xFF25, 0xF3);
		WRITEB(0xFF26, 0xF1);
		WRITEB(0xFF40, 0x91);
		WRITEB(0xFF42, 0x00);
		WRITEB(0xFF43, 0x00);
		WRITEB(0xFF45, 0x00);
		WRITEB(0xFF47, 0xFC);
		WRITEB(0xFF48, 0xFF);
		WRITEB(0xFF49, 0xFF);
		WRITEB(0xFF4A, 0x00);
		WRITEB(0xFF4B, 0x00);
		WRITEB(0xFFFF, 0x00);
	}
	else
	{
		m_af_reg_set(m_dmg, 0);
		BC = 0;
		DE = 0;
		HL = 0;
		PC = 0;
		SP = 0;
	}

	m_dmg->m_cpu->m_registers->m_flags.zero = 0;
	m_dmg->m_cpu->m_registers->m_flags.ngtv = 0;
	m_dmg->m_cpu->m_registers->m_flags.half = 0;
	m_dmg->m_cpu->m_registers->m_flags.crry = 0;


	// Set the CPU Ticks to 0
	m_dmg->m_cpu->m_cpu_ticks = 0;

	// Setup the PPU
	m_dmg->ppu->m_scanline = 0;
	m_dmg->ppu->m_verticalscroll = 0;
	m_dmg->ppu->m_horitzontalscroll = 0;

	// Set the current GPU Mode to HBLANK
	m_dmg->ppu->m_lcdc = 0;
	m_dmg->ppu->m_stat = M_GPU_HBLANK;

	// Setup Interrupts State (Disable Interrupts and Clear Interrupt's Flags)
	m_dmg->m_cpu->interrupts->m_master = 0;
	m_dmg->m_cpu->interrupts->m_enabled = 0;
	m_dmg->m_cpu->interrupts->m_flags = 0;
}

uint8_t m_fetch(m_dmg_t *m_dmg)
{
	if (m_dmg->m_memory->m_in_bootrom && PC >= 0xFF)
	{
		m_dmg->m_memory->m_in_bootrom = 0;
	}

	return (uint8_t) READB(PC);
}

uint8_t m_fetchopbyte(m_dmg_t *m_dmg)
{
	return (uint8_t) READB(PC + 1);
}

uint16_t m_fetchopword(m_dmg_t *m_dmg)
{
	uint8_t m_rb = READB(PC + 1);

	uint8_t m_lb = READB(PC + 2);

	uint16_t m_w = (((m_lb & 0xFF) << 8) | (m_rb & 0xFF));

	return (uint16_t) m_w;
}

#if defined(PREC23)
bool m_is_bit_set(uint8_t m_register, size_t m_bit)
{
	return 1 == ((m_register >> m_bit) & 1);
}
#endif

size_t m_exec(m_dmg_t *m_dmg)
{
	m_dmg->m_cpu->m_opcode = m_fetch(m_dmg);

#ifdef OPCODE_DEBUG
	printf("Current opcode: 0x%02X\n", m_dmg->m_cpu->m_opcode);
#endif

	m_dmg->m_cpu->m_boperand = 0;
	m_dmg->m_cpu->m_woperand = 0;

	if (m_gb_instr[m_dmg->m_cpu->m_opcode].m_operand == 1)
	{
		m_dmg->m_cpu->m_boperand = m_fetchopbyte(m_dmg);
	} else if (m_gb_instr[m_dmg->m_cpu->m_opcode].m_operand == 2) {
		m_dmg->m_cpu->m_woperand = m_fetchopword(m_dmg);
	}

	switch(m_gb_instr[m_dmg->m_cpu->m_opcode].m_operand)
	{
		case 0:
			if (m_gb_instr[m_dmg->m_cpu->m_opcode].m_funct == NULL)
			{
				printf("Unimplemented Opcode 0x%02X\n", m_dmg->m_cpu->m_opcode);
				m_printregs(m_dmg);
				exit(EXIT_FAILURE);
			} else {
				((void (*)(m_dmg_t *m_dmg))m_gb_instr[m_dmg->m_cpu->m_opcode].m_funct)(m_dmg);
			}
			break;
		
		case 1:
			if (m_gb_instr[m_dmg->m_cpu->m_opcode].m_funct == NULL)
			{
				printf("Unimplemented Opcode 0x%02X\n", m_dmg->m_cpu->m_opcode);
				m_printregs(m_dmg);
				exit(EXIT_FAILURE);
			} else {
				if ((m_dmg->m_cpu->m_opcode == 0x18) | (m_dmg->m_cpu->m_opcode == 0x20) | (m_dmg->m_cpu->m_opcode == 0x28))
				{
					((void (*)(m_dmg_t *m_dmg, uint8_t))m_gb_instr[m_dmg->m_cpu->m_opcode].m_funct)(m_dmg, (int8_t) m_dmg->m_cpu->m_boperand);
				} else {
					((void (*)(m_dmg_t *m_dmg, uint8_t))m_gb_instr[m_dmg->m_cpu->m_opcode].m_funct)(m_dmg, (uint8_t) m_dmg->m_cpu->m_boperand);
				}
			}
			break;

		case 2:
			if (m_gb_instr[m_dmg->m_cpu->m_opcode].m_funct == NULL)
			{
				printf("Unimplemented Opcode 0x%02X\n", m_dmg->m_cpu->m_opcode);
				m_printregs(m_dmg);
				exit(EXIT_FAILURE);
			} else {
				((void (*)(m_dmg_t *m_dmg, uint16_t))m_gb_instr[m_dmg->m_cpu->m_opcode].m_funct)(m_dmg, (uint16_t) m_dmg->m_cpu->m_woperand);
			}
			break;

		default:
			break;
	}

	if (m_dmg->m_cpu->m_opcode == 0xCB)
	{
		if (!m_dmg->m_speedhack) { m_dmg->m_cpu->m_cpu_ticks += m_ticks_by_cbopcode[m_fetchopbyte(m_dmg)]; } else { m_dmg->m_cpu->m_cpu_ticks = m_ticks_by_cbopcode[m_fetchopbyte(m_dmg)]; }
		return m_ticks_by_cbopcode[m_fetchopbyte(m_dmg)];
	}
	else
	{
		if (!m_dmg->m_speedhack) { m_dmg->m_cpu->m_cpu_ticks += m_ticks_by_opcode[m_dmg->m_cpu->m_opcode]; } else { m_dmg->m_cpu->m_cpu_ticks = m_ticks_by_opcode[m_dmg->m_cpu->m_opcode]; }
		return m_ticks_by_opcode[m_dmg->m_cpu->m_opcode];
	}
	
}

void m_printregs(m_dmg_t *m_dmg)
{
	printf("\n\033[1;31mGeneral-Purpose Registers:\033[0m\n");
	printf("\033[0;35mA:\033[0m 0x%02X, \033[0;35mF:\033[0m 0x%02X; \033[0;35mAF:\033[0m 0x%04X\n", A_REG, F, AF);
	printf("\033[0;35mB:\033[0m 0x%02X, \033[0;35mC:\033[0m 0x%02X; \033[0;35mBC:\033[0m 0x%04X\n", B_REG, C, BC);
	printf("\033[0;35mD:\033[0m 0x%02X, \033[0;35mE:\033[0m 0x%02X; \033[0;35mDE:\033[0m 0x%04X\n", D, E, DE);
	printf("\033[0;35mH:\033[0m 0x%02X, \033[0;35mL:\033[0m 0x%02X; \033[0;35mHL:\033[0m 0x%04X\n\n", H, L, HL);

	printf("\033[1;33mSegment Registers:\033[0:0m\n");
	printf("\033[1;35mSP:\033[0m 0x%04X\n\n", SP);

	printf("\033[1;32mProgram Flow Registers:\033[0:0m\n");
	printf("\033[1;35mPC:\033[0m 0x%04X\n\n", PC);

	printf("\033[1;34mInterrupts: \033[0m%d\n\n", (int) m_dmg->m_cpu->interrupts->m_master);

	printf("\033[1;35mFlags:\033[0:0m\n");

	printf("\033[1;35mZ: ");

#if defined(PREC23) || !defined(USE_GCC)
	if (FLAG_CHECK(ZERO))
#else
	if (m_is_bit_set(FLAGS, ZERO))
#endif
	{
		printf("\033[0m1   ");
	} else {
		printf("\033[0m0   ");
	}

	printf("\033[1;35mN: ");

#if defined(PREC23) || !defined(USE_GCC)
	if (FLAG_CHECK(NGTV))
#else
	if (m_is_bit_set(FLAGS, NGTV))
#endif
	{
		printf("\033[0m1   \n");
	} else {
		printf("\033[0m0   \n");
	}

	printf("\033[1;35mH: ");

#if defined(PREC23) || !defined(USE_GCC)
	if (FLAG_CHECK(HALF))
#else
	if (m_is_bit_set(FLAGS, HALF))
#endif
	{
		printf("\033[0m1   ");
	} else {
		printf("\033[0m0   ");
	}

	printf("\033[1;35mC: ");

#if defined(PREC23) || !defined(USE_GCC)
	if (FLAG_CHECK(CRRY))
#else
	if (m_is_bit_set(FLAGS, CRRY))
#endif
	{
		printf("\033[0m1   \n\n");
	} else {
		printf("\033[0m0   \n\n");
	}

	printf("\033[1;35mCurrent CPU Ticks:\033[0m %lu\n", m_dmg->m_cpu->m_cpu_ticks);
	printf("\033[1;35mCurrent GPU Ticks:\033[0m %lu\n", m_dmg->ppu->m_ticks);
}

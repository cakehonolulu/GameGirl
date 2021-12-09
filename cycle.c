#include <cycle.h>
#include <opcodes.h>
#include <gpu.h>
#include <int.h>

uint64_t m_cpu_ticks;

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

void m_init_registers()
{
	// If BootROM isn't loaded, bootstrap manually into cart area
	if (mmu->m_in_bootrom)
	{
		PC = 0x100;
		AF = 0x01B0;
		BC = 0x0013;
		DE = 0x00D8;
		HL = 0x014D;
		SP = 0xFFFE;

		m_regs.m_flags.zero = 0;
		m_regs.m_flags.ngtv = 0;
		m_regs.m_flags.half = 0;
		m_regs.m_flags.crry = 0;

		m_cpu_ticks = 0;

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
		AF = 0;
		BC = 0;
		DE = 0;
		HL = 0;
		PC = 0;
		SP = 0;

		m_regs.m_flags.zero = 0;
		m_regs.m_flags.ngtv = 0;
		m_regs.m_flags.half = 0;
		m_regs.m_flags.crry = 0;

		m_cpu_ticks = 0;
	}

	// Setup the PPU, point each GPU struct member to it's MMAP Addr.
	gpu.m_lcdc = mmu->gb_address_space[0xFF40];
	gpu.m_stat = mmu->gb_address_space[0xFF41];
	gpu.m_verticalscroll = mmu->gb_address_space[0xFF42];
	gpu.m_horitzontalscroll = mmu->gb_address_space[0xFF43];
	gpu.m_scanline = mmu->gb_address_space[0xFF44];

	// Set the current GPU Mode to HBLANK
	gpu.m_lcdc = 0;
	gpu.m_stat = M_GPU_HBLANK;

	// *Actually* set the values
	gpu.m_scanline = 0;
	gpu.m_verticalscroll = 0;
	gpu.m_horitzontalscroll = 0;

	// Setup Interrupts State
	ints.m_master = 0;
	ints.m_enabled = *mmu->gb_mmap.intenable;
	ints.m_flags = mmu->gb_address_space[0xFF0F];

	// Disable Interrupts and Clear Interrupt's Flags
	ints.m_enabled = 0;
	ints.m_flags = 0;
}

uint8_t m_fetch()
{
	if (!mmu->m_in_bootrom && PC >= 0xFF)
	{
		mmu->m_in_bootrom = 0x1;
	}

	return (uint8_t) READB(PC);
}

uint8_t m_fetchopbyte()
{
	return (uint8_t) READB(PC + 1);
}

uint16_t m_fetchopword()
{
	uint8_t m_rb = READB(PC + 1);

	uint8_t m_lb = READB(PC + 2);

	uint16_t m_w = (((m_lb & 0xFF) << 8) | (m_rb & 0xFF));

	return (uint16_t) m_w;
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

	if (m_opcode == 0xCB)
	{
		m_cpu_ticks += m_ticks_by_cbopcode[m_fetchopbyte()];
	} else {
		m_cpu_ticks += m_ticks_by_opcode[m_opcode];
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

	if (FLAG_CHECK(ZERO))
	{
		printf("\033[0m1   ");
	} else {
		printf("\033[0m0   ");
	}

	printf("\033[1;35mN: ");

	if (FLAG_CHECK(NGTV))
	{
		printf("\033[0m1   \n");
	} else {
		printf("\033[0m0   \n");
	}

	printf("\033[1;35mH: ");

	if (FLAG_CHECK(HALF))
	{
		printf("\033[0m1   ");
	} else {
		printf("\033[0m0   ");
	}

	printf("\033[1;35mC: ");

	if (FLAG_CHECK(CRRY))
	{
		printf("\033[0m1   \n");
	} else {
		printf("\033[0m0   \n");
	}

	printf("\033[1;35mCurrent CPU Ticks:\033[0m %lu\n", m_cpu_ticks);
	printf("\033[1;35mCurrent GPU Ticks:\033[0m %lu\n", gpu.m_ticks);
}

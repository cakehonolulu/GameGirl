#include <SDL2/SDL.h>
#include <gamegirl.h>
#include <opcodes.h>

extern uint8_t prev_pc;

SDL_Event m_dbgevent;

extern uint8_t m_boperand;
extern uint16_t m_woperand;

int m_run_debugger()
{
	printf("\e[1;1H\e[2J");
	printf("\033[1;32mEntered Debugging Step Mode!\033[0;0m\n");
	extern uint8_t m_opcode;

	uint8_t m_dbgopc = READB(PC);

	m_printregs();

	printf("\nLegend: \033[0;34mPrevious Instruction\033[0;0m, \033[0;33mCurrent Instruction\033[0;0m\n\n");

	if (m_gb_instr[m_opcode].m_operand == 0)
	{
		printf("\033[0;34m00:%04X  %02X ->\033[0;0m %s\n", prev_pc, READB(prev_pc), m_gb_instr[m_opcode].m_instr);
		printf("\033[0;33m00:%04X  %02X ->\033[0;0m %s\n\n", PC, READB(PC), m_gb_instr[m_dbgopc].m_instr);
	}

	if (m_gb_instr[m_opcode].m_operand == 1) {
		printf("\033[0;34m00:%04X  %02X ->\033[0;0m %s\n", prev_pc, READB(prev_pc), m_gb_instr[m_opcode].m_instr);
		printf("\033[0;33m00:%04X  %02X %02X ->\033[0;0m %s\n\n", PC, READB(PC), m_boperand, m_gb_instr[m_dbgopc].m_instr);
	}

	if (m_gb_instr[m_opcode].m_operand == 2)
	{
		printf("\033[0;34m00:%04X  %02X ->\033[0;0m %s\n", prev_pc, READB(prev_pc), m_gb_instr[m_opcode].m_instr);
		printf("\033[0;33m00:%04X  %02X %04X ->\033[0;0m %s\n\n", PC, READB(PC), m_woperand, m_gb_instr[m_dbgopc].m_instr);
	}

	printf("Press Enter to Step...\n");

	while (true)
	{
		while (SDL_PollEvent(&m_dbgevent))
		{
			if (m_dbgevent.type == SDL_QUIT)
			{
				goto exit;
			}

			if (m_dbgevent.type == SDL_KEYDOWN)
			{
				if (m_dbgevent.key.keysym.sym == SDLK_RETURN)
				{
					printf("\e[1;1H\e[2J");

					prev_pc = PC;

					m_exec();
					m_gpu_step();
					m_int_check();

					m_printregs();

					extern uint8_t m_opcode;

					printf("Legend: \033[0;34mPrevious Instruction\033[0;0m, \033[0;33mCurrent Instruction\033[0;0m\n\n");

					uint8_t m_dbgopc = READB(PC);

					printf("m_gb_instr[m_opcode].m_operand = %d\n", m_gb_instr[m_dbgopc].m_operand);

					if (m_gb_instr[m_dbgopc].m_operand == 0)
					{
						if (m_gb_instr[m_opcode].m_operand == 2)
						{
							printf("\033[0;34m00:%04X  %02X %02X %02X ->\033[0;0m %s\033[0;32m$\033[0;0m%04X\n", prev_pc, READB(prev_pc), READB(prev_pc + 1), READB(prev_pc + 2), m_gb_instr[m_opcode].m_instr, (READB(prev_pc + 2) >> 8) | (READB(prev_pc + 1) & 0xFF));
						} else if (m_gb_instr[m_opcode].m_operand == 1) {
							printf("\033[0;34m00:%04X  %02X %02X ->\033[0;0m %s\033[0;32m$\033[0;0m%04X\n", prev_pc, READB(prev_pc), READB(prev_pc + 1), m_gb_instr[m_opcode].m_instr, (READB(prev_pc + 1)));
						} else if (m_gb_instr[m_opcode].m_operand == 0) {
							printf("\033[0;34m00:%04X  %02X ->\033[0;0m %s\n", prev_pc, READB(prev_pc), m_gb_instr[m_opcode].m_instr);
						}

						printf("\033[0;33m00:%04X  %02X ->\033[0;0m %s\n\n", PC, READB(PC), m_gb_instr[m_dbgopc].m_instr);
					}

					if (m_gb_instr[m_dbgopc].m_operand == 1)
					{
						if (m_gb_instr[m_opcode].m_operand == 2)
						{
							printf("\033[0;34m00:%04X  %02X %02X %02X ->\033[0;0m %s\033[0;32m$\033[0;0m%04X\n", prev_pc, READB(prev_pc), READB(prev_pc + 1), READB(prev_pc + 2), m_gb_instr[m_opcode].m_instr, (READB(prev_pc + 2) >> 8) | (READB(prev_pc + 1) & 0xFF));
						} else if (m_gb_instr[m_opcode].m_operand == 1) {
							printf("\033[0;34m00:%04X  %02X %02X ->\033[0;0m %s\033[0;32m$\033[0;0m%04X\n", prev_pc, READB(prev_pc), READB(prev_pc + 1), m_gb_instr[m_opcode].m_instr, (READB(prev_pc + 1)));
						} else if (m_gb_instr[m_opcode].m_operand == 0) {
							printf("\033[0;34m00:%04X  %02X ->\033[0;0m %s\n", prev_pc, READB(prev_pc), m_gb_instr[m_opcode].m_instr);				
						}

						printf("\033[0;33m00:%04X  %02X %02X ->\033[0;0m %s\033[0;32m$\033[0;0m%02X\n\n", PC, READB(PC), READB(PC + 1), m_gb_instr[m_dbgopc].m_instr, READB(PC + 1));
					}

					if (m_gb_instr[m_dbgopc].m_operand == 2)
					{
						if (m_gb_instr[m_opcode].m_operand == 2)
						{
							printf("\033[0;34m00:%04X  %02X %02X %02X ->\033[0;0m %s\033[0;32m$\033[0;0m%04X\n", prev_pc, READB(prev_pc), READB(prev_pc + 1), READB(prev_pc + 2), m_gb_instr[m_opcode].m_instr, (READB(prev_pc + 2) >> 8) | (READB(prev_pc + 1) & 0xFF));
						} else if (m_gb_instr[m_opcode].m_operand == 1) {
							printf("\033[0;34m00:%04X  %02X %02X ->\033[0;0m %s\033[0;32m$\033[0;0m%04X\n", prev_pc, READB(prev_pc), READB(prev_pc + 1), m_gb_instr[m_opcode].m_instr, (READB(prev_pc + 1)));
						} else if (m_gb_instr[m_opcode].m_operand == 0) {
							printf("\033[0;34m00:%04X  %02X ->\033[0;0m %s\n", prev_pc, READB(prev_pc), m_gb_instr[m_opcode].m_instr);
						}

						printf("\033[0;33m00:%04X  %02X %02X %02X ->\033[0;0m %s\033[0;32m$\033[0;0m%04X\n\n", PC, READB(PC), READB(PC + 1), READB(PC + 2), m_gb_instr[m_dbgopc].m_instr, (READB(PC + 2) >> 8) | (READB(PC + 1) & 0xFF));
					}
							
					printf("Press Enter to Step...\n");
				}
			}
		}
	}

exit:
	// Free MMU data
	mmu_halt();

	SDL_Quit();

	return EXIT_SUCCESS;
}
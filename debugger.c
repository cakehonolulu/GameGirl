#include <SDL2/SDL.h>
#include <gamegirl.h>
#include <opcodes.h>
#include <debugger.h>
#include <cb_opcodes.h>
#include <ppu.h>

#define NEXT_BYTE m_dmg->m_cpu->m_boperand
#define NEXT_WORD m_dmg->m_cpu->m_woperand

int m_run_debugger(m_dmg_t *m_dmg)
{
	SDL_Event m_dbgevent;

	printf("\e[1;1H\e[2J");
	printf("\033[1;32mEntered Debugging Step Mode!\033[0;0m");

	uint8_t m_dbgopc = READB(PC);

	m_printregs(m_dmg);
	
	printf("Legend: \033[0;34mPrevious Instruction\033[0;0m, \033[0;33mCurrent Instruction\033[0;0m\n\n");

	// Check if we're on the start of the BootROM (Don't print previous opcode as it doesn't exist)
	if (PC)
	{
		/* Enter Debug First Opcode (Previous) */
		if (m_dmg->m_cpu->m_opcode != 0xCB)
		{
			if (m_gb_instr[m_dmg->m_cpu->m_opcode].m_operand == 0)
			{
				printf("\033[0;34m00:%04X  %02X   \033[0;0m       %s\n", m_dmg->m_cpu->prev_pc, READB(m_dmg->m_cpu->prev_pc), m_gb_instr[m_dmg->m_cpu->m_opcode].m_instr);
			}
			else
			if (m_gb_instr[m_dmg->m_cpu->m_opcode].m_operand == 1)
			{
				if ((m_dmg->m_cpu->m_opcode == 0x18) | (m_dmg->m_cpu->m_opcode == 0x20) | (m_dmg->m_cpu->m_opcode == 0x28))
				{
					printf("\033[0;34m00:%04X  %02X %02X      \033[0;0m %s$%04X (%d)\n", m_dmg->m_cpu->prev_pc, READB(m_dmg->m_cpu->prev_pc), READB(m_dmg->m_cpu->prev_pc + 1), m_gb_instr[m_dmg->m_cpu->m_opcode].m_instr, ((m_dmg->m_cpu->prev_pc + 2) + (int8_t) READB(m_dmg->m_cpu->prev_pc + 1)),(int8_t) READB(m_dmg->m_cpu->prev_pc + 1));
				}
				else
				{
					printf("\033[0;34m00:%04X  %02X         \033[0;0m %s\n", m_dmg->m_cpu->prev_pc, READB(m_dmg->m_cpu->prev_pc), m_gb_instr[m_dmg->m_cpu->m_opcode].m_instr);
				}
			}
			else
			if (m_gb_instr[m_dmg->m_cpu->m_opcode].m_operand == 2)
			{
				printf("\033[0;34m00:%04X  %02X %02X %02X\033[0;0m    %s$%04X\n", m_dmg->m_cpu->prev_pc, READB(m_dmg->m_cpu->prev_pc), READB(m_dmg->m_cpu->prev_pc + 1), READB(m_dmg->m_cpu->prev_pc + 2), m_gb_instr[m_dmg->m_cpu->m_opcode].m_instr, ((READB(m_dmg->m_cpu->prev_pc + 2) << 8) | (READB(m_dmg->m_cpu->prev_pc + 1))));
			}
		}
		else
		{
			// Extended (0xCB) Opcode Handling
			printf("\033[0;34m00:%04X  %02X %02X      \033[0;0m %s\n", m_dmg->m_cpu->prev_pc, READB(m_dmg->m_cpu->prev_pc), READB(m_dmg->m_cpu->prev_pc + 1), m_gb_instr_cb[READB(m_dmg->m_cpu->prev_pc + 1)].m_instr);
		}
	}

	if (m_dbgopc != 0xCB)
	{
		/* Enter Debug Second Opcode (Current) */
		if (m_gb_instr[m_dbgopc].m_operand == 0)
		{
			printf("\033[0;33m00:%04X  %02X  	  ->\033[0;0m %s\n\n", PC, READB(PC), m_gb_instr[m_dbgopc].m_instr);
		}
		else
		if (m_gb_instr[m_dbgopc].m_operand == 1)
		{
			if ((m_dbgopc == 0x18) | (m_dbgopc == 0x20) | (m_dbgopc == 0x28))
			{
				printf("\033[0;33m00:%04X  %02X %02X    ->\033[0;0m %s$%04X (%d)\n\n", PC, READB(PC), READB(PC + 1), m_gb_instr[m_dbgopc].m_instr, ((PC + 2) + (int8_t) READB(PC + 1)),(int8_t) READB(PC + 1));
			}
			else
			{
				printf("\033[0;33m00:%04X  %02X %02X    ->\033[0;0m %s$%02X\n\n", PC, READB(PC), READB(PC + 1), m_gb_instr[m_dbgopc].m_instr, READB(PC + 1));
			}
		}
		else
		if (m_gb_instr[m_dbgopc].m_operand == 2)
		{
			printf("\033[0;33m00:%04X  %02X %02X %02X ->\033[0;0m %s$%04X\n\n", PC, READB(PC), READB(PC + 1), READB(PC + 2), m_gb_instr[m_dbgopc].m_instr, ((READB(PC + 2) << 8) | (READB(PC + 1))));
		}
	}
	else
	{
		printf("\033[0;33m00:%04X  %02X %02X    ->\033[0;0m %s\n\n", PC, READB(PC), READB(PC + 1), m_gb_instr_cb[READB(PC + 1)].m_instr);
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

					m_dmg->m_cpu->prev_pc = PC;

					size_t m_cycles = m_exec(m_dmg);
					m_ppu_step(m_dmg, m_cycles);
					m_interrupt_check(m_dmg);

					m_printregs(m_dmg);

					printf("Legend: \033[0;34mPrevious Instruction\033[0;0m, \033[0;33mCurrent Instruction\033[0;0m\n\n");

					uint8_t m_dbgopc = READB(PC);

					if (m_dmg->m_cpu->m_opcode != 0xCB)
					{
						if (m_gb_instr[m_dmg->m_cpu->m_opcode].m_operand == 0)
						{
							printf("\033[0;34m00:%04X  %02X   \033[0;0m       %s\n", m_dmg->m_cpu->prev_pc, READB(m_dmg->m_cpu->prev_pc), m_gb_instr[m_dmg->m_cpu->m_opcode].m_instr);
						}
						else
						if (m_gb_instr[m_dmg->m_cpu->m_opcode].m_operand == 1)
						{
							if ((m_dmg->m_cpu->m_opcode == 0x18) | (m_dmg->m_cpu->m_opcode == 0x20) | (m_dmg->m_cpu->m_opcode == 0x28))
							{
								printf("\033[0;34m00:%04X  %02X %02X      \033[0;0m %s$%04X (%d)\n", m_dmg->m_cpu->prev_pc, READB(m_dmg->m_cpu->prev_pc), READB(m_dmg->m_cpu->prev_pc + 1), m_gb_instr[m_dmg->m_cpu->m_opcode].m_instr, ((m_dmg->m_cpu->prev_pc + 2) + (int8_t) READB(m_dmg->m_cpu->prev_pc + 1)),(int8_t) READB(m_dmg->m_cpu->prev_pc + 1));
							}
							else
							{
								printf("\033[0;34m00:%04X  %02X %02X      \033[0;0m %s$%02X\n", m_dmg->m_cpu->prev_pc, READB(m_dmg->m_cpu->prev_pc), READB(m_dmg->m_cpu->prev_pc + 1), m_gb_instr[m_dmg->m_cpu->m_opcode].m_instr, READB(m_dmg->m_cpu->prev_pc + 1));
							}
						}
						else
						if (m_gb_instr[m_dmg->m_cpu->m_opcode].m_operand == 2)
						{
							printf("\033[0;34m00:%04X  %02X %02X %02X\033[0;0m    %s$%04X\n", m_dmg->m_cpu->prev_pc, READB(m_dmg->m_cpu->prev_pc), READB(m_dmg->m_cpu->prev_pc + 1), READB(m_dmg->m_cpu->prev_pc + 2), m_gb_instr[m_dmg->m_cpu->m_opcode].m_instr, ((READB(m_dmg->m_cpu->prev_pc + 2) << 8) | (READB(m_dmg->m_cpu->prev_pc + 1))));
						}
					}
					else
					{
						// Extended (0xCB) Opcode Handling
						printf("\033[0;34m00:%04X  %02X %02X      \033[0;0m %s\n", m_dmg->m_cpu->prev_pc, READB(m_dmg->m_cpu->prev_pc), READB(m_dmg->m_cpu->prev_pc + 1), m_gb_instr_cb[READB(m_dmg->m_cpu->prev_pc + 1)].m_instr);
					}

					if (m_dbgopc != 0xCB)
					{
						/* Enter Debug Second Opcode (Current) */
						if (m_gb_instr[m_dbgopc].m_operand == 0)
						{
							printf("\033[0;33m00:%04X  %02X  	  ->\033[0;0m %s\n\n", PC, READB(PC), m_gb_instr[m_dbgopc].m_instr);
						}
						else
						if (m_gb_instr[m_dbgopc].m_operand == 1)
						{
							if ((m_dbgopc == 0x18) | (m_dbgopc == 0x20) | (m_dbgopc == 0x28))
							{
								printf("\033[0;33m00:%04X  %02X %02X    ->\033[0;0m %s$%04X (%d)\n\n", PC, READB(PC), READB(PC + 1), m_gb_instr[m_dbgopc].m_instr, ((PC + 2) + (int8_t) READB(PC + 1)),(int8_t) READB(PC + 1));
							}
							else
							{
								printf("\033[0;33m00:%04X  %02X %02X    ->\033[0;0m %s$%02X\n\n", PC, READB(PC), READB(PC + 1), m_gb_instr[m_dbgopc].m_instr, READB(PC + 1));
							}
						}
						else
						if (m_gb_instr[m_dbgopc].m_operand == 2)
						{
							printf("\033[0;33m00:%04X  %02X %02X %02X ->\033[0;0m %s$%04X\n\n", PC, READB(PC), READB(PC + 1), READB(PC + 2), m_gb_instr[m_dbgopc].m_instr, ((READB(PC + 2) << 8) | (READB(PC + 1))));
						}
					}
					else
					{
						printf("\033[0;33m00:%04X  %02X %02X    ->\033[0;0m %s\n\n", PC, READB(PC), READB(PC + 1), m_gb_instr_cb[READB(PC + 1)].m_instr);
					}
							
					printf("Press Enter to Step...\n");
				}
			}
		}
	}

exit:
	// Free MMU data
	mmu_halt(m_dmg);

	SDL_Quit();

	return EXIT_SUCCESS;
}

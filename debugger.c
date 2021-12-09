#include <SDL2/SDL.h>
#include <gamegirl.h>
#include <opcodes.h>
#include <cb_opcodes.h>

SDL_Event m_dbgevent;

extern uint8_t m_boperand;
extern uint16_t m_woperand;
extern uint8_t m_opcode;
extern uint8_t prev_pc;

#define PREV_PC prev_pc
#define NEXT_BYTE m_boperand
#define NEXT_WORD m_woperand

int m_run_debugger()
{
	printf("\e[1;1H\e[2J");
	printf("\033[1;32mEntered Debugging Step Mode!\033[0;0m");

	uint8_t m_dbgopc = READB(PC);

	m_printregs();


	printf("m_gb_instr[m_opcode].m_operand = %d\n", m_gb_instr[m_dbgopc].m_operand);
	printf("m_gb_instr[m_dbgopc].m_operand = %d\n", m_gb_instr[m_dbgopc].m_operand);

	printf("Legend: \033[0;34mPrevious Instruction\033[0;0m, \033[0;33mCurrent Instruction\033[0;0m\n\n");

	// Check if we're on the start of the BootROM (Don't print previous opcode as it doesn't exist)
	if (PC)
	{
		/* Enter Debug First Opcode (Previous) */
		if (m_opcode != 0xCB)
		{
			if (m_gb_instr[m_opcode].m_operand == 0)
			{
				printf("\033[0;34m00:%04X  %02X   \033[0;0m       %s\n", PREV_PC, READB(PREV_PC), m_gb_instr[m_opcode].m_instr);
			}
			else
			if (m_gb_instr[m_opcode].m_operand == 1)
			{
				if ((m_opcode == 0x18) | (m_opcode == 0x20) | (m_opcode == 0x28))
				{
					printf("\033[0;34m00:%04X  %02X %02X      \033[0;0m %s$%04X (%d)\n", PREV_PC, READB(PREV_PC), READB(PREV_PC + 1), m_gb_instr[m_opcode].m_instr, ((PREV_PC + 2) + (int8_t) READB(PREV_PC + 1)),(int8_t) READB(PREV_PC + 1));
				}
				else
				{
					printf("\033[0;34m00:%04X  %02X         \033[0;0m %s\n", PREV_PC, READB(PREV_PC), m_gb_instr[m_opcode].m_instr);
				}
			}
			else
			if (m_gb_instr[m_opcode].m_operand == 2)
			{
				printf("\033[0;34m00:%04X  %02X %02X %02X\033[0;0m    %s$%04X\n", PREV_PC, READB(PREV_PC), READB(PREV_PC + 1), READB(PREV_PC + 2), m_gb_instr[m_opcode].m_instr, ((READB(PREV_PC + 2) << 8) | (READB(PREV_PC + 1))));
			}
		}
		else
		{
			// Extended (0xCB) Opcode Handling
			printf("\033[0;34m00:%04X  %02X %02X      \033[0;0m %s\n", PREV_PC, READB(PREV_PC), READB(PREV_PC + 1), m_gb_instr_cb[READB(PREV_PC + 1)].m_instr);
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

					prev_pc = PC;

					m_exec();
					m_gpu_step();
					m_int_check();

					m_printregs();


					printf("m_gb_instr[m_opcode].m_operand = %d\n", m_gb_instr[m_opcode].m_operand);
					printf("m_gb_instr[m_dbgopc].m_operand = %d\n", m_gb_instr[m_dbgopc].m_operand);


					printf("Legend: \033[0;34mPrevious Instruction\033[0;0m, \033[0;33mCurrent Instruction\033[0;0m\n\n");

					uint8_t m_dbgopc = READB(PC);

					if (m_opcode != 0xCB)
					{
						if (m_gb_instr[m_opcode].m_operand == 0)
						{
							printf("\033[0;34m00:%04X  %02X   \033[0;0m       %s\n", PREV_PC, READB(PREV_PC), m_gb_instr[m_opcode].m_instr);
						}
						else
						if (m_gb_instr[m_opcode].m_operand == 1)
						{
							if ((m_opcode == 0x18) | (m_opcode == 0x20) | (m_opcode == 0x28))
							{
								printf("\033[0;34m00:%04X  %02X %02X      \033[0;0m %s$%04X (%d)\n", PREV_PC, READB(PREV_PC), READB(PREV_PC + 1), m_gb_instr[m_opcode].m_instr, ((PREV_PC + 2) + (int8_t) READB(PREV_PC + 1)),(int8_t) READB(PREV_PC + 1));
							}
							else
							{
								printf("\033[0;34m00:%04X  %02X %02X      \033[0;0m %s$%02X\n", PREV_PC, READB(PREV_PC), READB(PREV_PC + 1), m_gb_instr[m_opcode].m_instr, READB(PREV_PC + 1));
							}
						}
						else
						if (m_gb_instr[m_opcode].m_operand == 2)
						{
							printf("\033[0;34m00:%04X  %02X %02X %02X\033[0;0m    %s$%04X\n", PREV_PC, READB(PREV_PC), READB(PREV_PC + 1), READB(PREV_PC + 2), m_gb_instr[m_opcode].m_instr, ((READB(PREV_PC + 2) << 8) | (READB(PREV_PC + 1))));
						}
					}
					else
					{
						// Extended (0xCB) Opcode Handling
						printf("\033[0;34m00:%04X  %02X %02X      \033[0;0m %s\n", PREV_PC, READB(PREV_PC), READB(PREV_PC + 1), m_gb_instr_cb[READB(PREV_PC + 1)].m_instr);
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
	mmu_halt();

	SDL_Quit();

	return EXIT_SUCCESS;
}
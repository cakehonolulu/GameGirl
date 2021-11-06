#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <GL/gl.h>
#include "include/gamegirl.h"
#include "include/mmu.h"
#include "include/cycle.h"
#include "include/opcodes.h"
#include "include/int.h"

// Init MMU
gb_mmu_t *mmu;
// Declare the Registers
gb_registers_t m_regs;

int main(int argc, char **argv)
{
	printf("GameGirl - A C-21 Multiplatform Game Boy Emulator\n");

	if (argc < 2)
	{
		printf("Usage: ./gamegirl [bootrom] [progname]\n");
		printf("Command-line switches:\n");
		return EXIT_FAILURE;
	}

	// Declare a char pointer with the name of the filename to load
	[[maybe_unused]] const char *m_bootromname = NULL;
	[[maybe_unused]] const char *m_programname = NULL;

	[[maybe_unused]] bool m_foundbootrom = false;
	[[maybe_unused]] bool m_foundprogram = false;

	int32_t m_breakpoint = -1;

	for (int i = 1; i < argc; i++)
	{
		if (m_foundbootrom != true)
		{
			if ((strstr(argv[i], ".gb") != NULL) || (strstr(argv[i], ".rom") != NULL))
			{
				m_programname = argv[i];
				m_foundprogram = true;
			} else if (strstr(argv[i], ".bin") != NULL) {
				m_bootromname = argv[i];
				m_foundbootrom = true;
			}
		} else {
			if (m_foundbootrom == true)
			{
				if (argc > 2)
				{
					uint32_t conv = strtol(argv[2], NULL, 0);

					m_breakpoint = conv;

					printf("0x%02X\n", m_breakpoint);
				}
			} else {
				printf("Unknown argument: %s\n", argv[i]);
				exit(EXIT_FAILURE);
			}
		}
	}

	FILE *m_bootrom;

	m_bootrom = fopen(m_bootromname, "rb");

	// Check if the file has been opened
	if(m_bootrom == NULL)
	{
		printf("Could not open the BootROM file, exiting...\n");
		return EXIT_FAILURE;
	} else {
		printf("BootROM loaded successfully\n");
	}

	// Get file size in bytes
	fseek(m_bootrom, 0, SEEK_END);
	size_t m_bootromsz = ftell(m_bootrom);
	fseek(m_bootrom, 0, SEEK_SET);

	// Allocate a buffer for the program
	unsigned char *m_bootrom_buf;
	m_bootrom_buf = (unsigned char*) malloc(sizeof(unsigned char) * m_bootromsz);

	// Error out on memory exhaustion
	if (m_bootrom_buf == NULL)
	{
		printf("Couldn't allocate memory, exiting...\n");
		return EXIT_FAILURE;
	}

	// Load the file into host memory
	fread(m_bootrom_buf, sizeof(unsigned char), m_bootromsz, m_bootrom); 

	printf("Program size: %d bytes\n", (unsigned int) m_bootromsz);

	// Init MMU
	mmu = mmu_init();

	// Init Address Space
	m_init_address_space();

	// Load Bootrom
	m_load_bootrom(m_bootrom_buf);

	// Initialize Registers
	m_init_registers();

	m_regs.isUnimplemented = false;

	uint8_t prev_pc;

	extern uint8_t m_boperand;
	extern uint16_t m_woperand;
/*
	// Declare both the window and Context to use SDL2 abilities
	SDL_Window   *m_window;
	SDL_GLContext m_context;
	SDL_Event m_event;

	// Init SDL2
	// SDL_INIT_VIDEO automatically enables SDL2 Events, we can OR SDL_INIT_AUDIO and SDL_INIT_TIMER if needed in the future
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		SDL_Log("Unable to initialize SDL2: %s", SDL_GetError());
        return EXIT_FAILURE;
	}

	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 2 );
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 );

	// Create a 160 x 144 (px) window
	m_window = SDL_CreateWindow("GameGirl (SDL2)", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
							  160, 144, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

	// Check if Window could be crafted
	if (m_window == NULL)
	{
        printf("Could not create SDL2 Window: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    m_context = SDL_GL_CreateContext(m_window);
*/
	while (true)
	{
		prev_pc = PC;

		/*while (SDL_PollEvent(&m_event))
		{
			if (m_event.type == SDL_QUIT)
			{
				goto exit;
			}
		}
*/
		// Start fetching & executing instructions
		m_exec();

		// Execute the GPU subsystem
		m_gpu_step();
		m_int_check();
/*
		glViewport(0, 0, 160, 144);
		glClearColor(1.f, 0.f, 1.f, 0.f);
		glClear(GL_COLOR_BUFFER_BIT);

		SDL_GL_SwapWindow(m_window);
*/
		if ((m_breakpoint != -1) && PC == m_breakpoint)
		{
			printf("\e[1;1H\e[2J");
			printf("\033[1;32mEntered Debugging Step Mode!\033[0;0m\n");

			extern uint8_t m_opcode;

			uint8_t m_dbgopc = mmu_read_byte(PC);

			m_printregs();

			printf("\nLegend: \033[0;34mPrevious Instruction\033[0;0m, \033[0;33mCurrent Instruction\033[0;0m\n\n");

			if (m_gb_instr[m_opcode].m_operand == 0)
			{
				printf("\033[0;34m00:%04X  %02X ->\033[0;0m %s\n", prev_pc, mmu_read_byte(prev_pc), m_gb_instr[m_opcode].m_instr);
				printf("\033[0;33m00:%04X  %02X ->\033[0;0m %s\n\n", PC, mmu_read_byte(PC), m_gb_instr[m_dbgopc].m_instr);
			}

			if (m_gb_instr[m_opcode].m_operand == 1) {
				printf("\033[0;34m00:%04X  %02X ->\033[0;0m %s\n", prev_pc, mmu_read_byte(prev_pc), m_gb_instr[m_opcode].m_instr);
				printf("\033[0;33m00:%04X  %02X %02X ->\033[0;0m %s\n\n", PC, mmu_read_byte(PC), m_boperand, m_gb_instr[m_dbgopc].m_instr);
			}

			if (m_gb_instr[m_opcode].m_operand == 2) {
				printf("\033[0;34m00:%04X  %02X ->\033[0;0m %s\n", prev_pc, mmu_read_byte(prev_pc), m_gb_instr[m_opcode].m_instr);
				printf("\033[0;33m00:%04X  %02X %04X ->\033[0;0m %s\n\n", PC, mmu_read_byte(PC), m_woperand, m_gb_instr[m_dbgopc].m_instr);
			}
			

			printf("Press Enter to Step...\n");

			while (true)
			{
				while (getchar())
				{
					printf("\e[1;1H\e[2J");

					prev_pc = PC;

					m_exec();
					m_gpu_step();
					m_int_check();

					m_printregs();

					extern uint8_t m_opcode;

					printf("Legend: \033[0;34mPrevious Instruction\033[0;0m, \033[0;33mCurrent Instruction\033[0;0m\n\n");

					uint8_t m_dbgopc = mmu_read_byte(PC);

					printf("m_gb_instr[m_opcode].m_operand = %d\n", m_gb_instr[m_dbgopc].m_operand);

					if (m_gb_instr[m_dbgopc].m_operand == 0)
					{
						if (m_gb_instr[m_opcode].m_operand == 2)
						{
							printf("\033[0;34m00:%04X  %02X %02X %02X ->\033[0;0m %s\033[0;32m$\033[0;0m%04X\n", prev_pc, mmu_read_byte(prev_pc), mmu_read_byte(prev_pc + 1), mmu_read_byte(prev_pc + 2), m_gb_instr[m_opcode].m_instr, (mmu_read_byte(prev_pc + 2) >> 8) | (mmu_read_byte(prev_pc + 1) & 0xFF));
						} else if (m_gb_instr[m_opcode].m_operand == 1) {
							printf("\033[0;34m00:%04X  %02X %02X ->\033[0;0m %s\033[0;32m$\033[0;0m%04X\n", prev_pc, mmu_read_byte(prev_pc), mmu_read_byte(prev_pc + 1), m_gb_instr[m_opcode].m_instr, (mmu_read_byte(prev_pc + 1)));
						} else if (m_gb_instr[m_opcode].m_operand == 0) {
							printf("\033[0;34m00:%04X  %02X ->\033[0;0m %s\n", prev_pc, mmu_read_byte(prev_pc), m_gb_instr[m_opcode].m_instr);
						}

						printf("\033[0;33m00:%04X  %02X ->\033[0;0m %s\n\n", PC, mmu_read_byte(PC), m_gb_instr[m_dbgopc].m_instr);
					}

					if (m_gb_instr[m_dbgopc].m_operand == 1)
					{
						if (m_gb_instr[m_opcode].m_operand == 2)
						{
							printf("\033[0;34m00:%04X  %02X %02X %02X ->\033[0;0m %s\033[0;32m$\033[0;0m%04X\n", prev_pc, mmu_read_byte(prev_pc), mmu_read_byte(prev_pc + 1), mmu_read_byte(prev_pc + 2), m_gb_instr[m_opcode].m_instr, (mmu_read_byte(prev_pc + 2) >> 8) | (mmu_read_byte(prev_pc + 1) & 0xFF));
						} else if (m_gb_instr[m_opcode].m_operand == 1) {
							printf("\033[0;34m00:%04X  %02X %02X ->\033[0;0m %s\033[0;32m$\033[0;0m%04X\n", prev_pc, mmu_read_byte(prev_pc), mmu_read_byte(prev_pc + 1), m_gb_instr[m_opcode].m_instr, (mmu_read_byte(prev_pc + 1)));
						} else if (m_gb_instr[m_opcode].m_operand == 0) {
							printf("\033[0;34m00:%04X  %02X ->\033[0;0m %s\n", prev_pc, mmu_read_byte(prev_pc), m_gb_instr[m_opcode].m_instr);
							
						}

						printf("\033[0;33m00:%04X  %02X %02X ->\033[0;0m %s\033[0;32m$\033[0;0m%02X\n\n", PC, mmu_read_byte(PC), mmu_read_byte(PC + 1), m_gb_instr[m_dbgopc].m_instr, mmu_read_byte(PC + 1));
					}

					if (m_gb_instr[m_dbgopc].m_operand == 2)
					{
						if (m_gb_instr[m_opcode].m_operand == 2)
						{
							printf("\033[0;34m00:%04X  %02X %02X %02X ->\033[0;0m %s\033[0;32m$\033[0;0m%04X\n", prev_pc, mmu_read_byte(prev_pc), mmu_read_byte(prev_pc + 1), mmu_read_byte(prev_pc + 2), m_gb_instr[m_opcode].m_instr, (mmu_read_byte(prev_pc + 2) >> 8) | (mmu_read_byte(prev_pc + 1) & 0xFF));
						} else if (m_gb_instr[m_opcode].m_operand == 1) {
							printf("\033[0;34m00:%04X  %02X %02X ->\033[0;0m %s\033[0;32m$\033[0;0m%04X\n", prev_pc, mmu_read_byte(prev_pc), mmu_read_byte(prev_pc + 1), m_gb_instr[m_opcode].m_instr, (mmu_read_byte(prev_pc + 1)));
						} else if (m_gb_instr[m_opcode].m_operand == 0) {
							printf("\033[0;34m00:%04X  %02X ->\033[0;0m %s\n", prev_pc, mmu_read_byte(prev_pc), m_gb_instr[m_opcode].m_instr);
						}

						printf("\033[0;33m00:%04X  %02X %02X %02X ->\033[0;0m %s\033[0;32m$\033[0;0m%04X\n\n", PC, mmu_read_byte(PC), mmu_read_byte(PC + 1), mmu_read_byte(PC + 2), m_gb_instr[m_dbgopc].m_instr, (mmu_read_byte(PC + 2) >> 8) | (mmu_read_byte(PC + 1) & 0xFF));
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

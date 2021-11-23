#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <GL/gl.h>
#include <gamegirl.h>
#include <mmu.h>
#include <cycle.h>
#include <opcodes.h>
#include <int.h>

// Init MMU
gb_mmu_t *mmu;

// Declare the Registers
gb_registers_t m_regs;

// Declare both, Window and Renderer, to be used by SDL2
SDL_Window   *m_window;
SDL_Renderer *m_renderer;
SDL_Texture *m_texture;

// Declare an SDL2 Event Handler
SDL_Event m_event;

int main(int argc, char **argv)
{
	printf("GameGirl - A C-21 Multiplatform Game Boy Emulator\n");

#ifdef UNIX
	if (argc < 2)
	{
		printf("Usage: ./gamegirl [bootrom] [progname]\n");
		printf("Command-line switches:\n");
		return EXIT_FAILURE;
	}
#endif

	// Init MMU
	mmu = mmu_init();

	// Init Address Space
	m_init_address_space();

#ifdef UNIX
	// Declare a char pointer with the names of the filenames to load
	[[maybe_unused]] const char *m_bootromname = NULL;
	[[maybe_unused]] const char *m_programname = NULL;

	// Declare booleans to check if we found the programs
	[[maybe_unused]] bool m_foundbootrom = false;
	[[maybe_unused]] bool m_foundprogram = false;
#endif

	uint32_t m_breakpoint = 0xFFFFFFFF;

#ifdef UNIX
	for (int i = 1; i < argc; i++)
	{
		if (m_foundbootrom != true || m_foundprogram != true)
		{
			if ((strstr(argv[i], ".gb") != NULL) || (strstr(argv[i], ".rom") != NULL))
			{
				m_programname = argv[i];
				m_foundprogram = true;
				printf("ROM File: %s\n", m_programname);
			}
			else
			if (strstr(argv[i], ".bin") != NULL)
			{
				m_bootromname = argv[i];
				m_foundbootrom = true;
				printf("BootROM File: %s\n", m_bootromname);
			}
		}
		else
		{
			if (m_foundbootrom == true)
			{
				if (argc < 3 && m_foundprogram != true)
				{
					uint32_t conv = strtol(argv[2], NULL, 0);

					m_breakpoint = conv;

					printf("0x%02X\n", m_breakpoint);
				}
				else
				if (argc < 4 && m_foundprogram == true)
				{
					uint32_t conv = strtol(argv[3], NULL, 0);

					m_breakpoint = conv;

					printf("0x%02X\n", m_breakpoint);
				}
			}
			else
			if (m_foundbootrom != true && m_foundprogram == true)
			{
				if (argc < 3 && m_foundbootrom != true)
				{
					uint32_t conv = strtol(argv[2], NULL, 0);

					m_breakpoint = conv;

					printf("0x%02X\n", m_breakpoint);
				}
			}
			else
			{
				printf("Unknown argument: %s\n", argv[i]);
				exit(EXIT_FAILURE);
			}
		}
	}

	if (m_foundbootrom)
	{
#endif
		FILE *m_bootrom;

#ifdef UNIX
		m_bootrom = fopen(m_bootromname, "rb");
#endif

#ifdef WIN32
		m_bootrom = fopen("bootrom.bin", "rb");
#endif

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

		printf("BootROM Size: %d bytes\n", (unsigned int) m_bootromsz);
		
		// Load Bootrom
		m_load_bootrom(m_bootrom_buf);
#ifdef UNIX
	}
#endif

#ifdef UNIX
	if (m_foundprogram)
	{
#endif
		FILE *m_romfile;

#ifdef UNIX
		m_romfile = fopen(m_programname, "rb");
#endif

#ifdef WIN32
		m_romfile = fopen("tetris.gb", "rb");
#endif

		// Check if the file has been opened
		if(m_romfile == NULL)
		{
			printf("Could not open the ROM File, exiting...\n");
			return EXIT_FAILURE;
		} else {
			printf("ROM loaded successfully\n");
		}

		// Get file size in bytes
		fseek(m_romfile, 0, SEEK_END);
		size_t m_romsz = ftell(m_romfile);
		fseek(m_romfile, 0, SEEK_SET);

		// Allocate a buffer for the program
		unsigned char *m_rom_buf;
		m_rom_buf = (unsigned char*) malloc(sizeof(unsigned char) * m_romsz);

		// Error out on memory exhaustion
		if (m_rom_buf == NULL)
		{
			printf("Couldn't allocate memory, exiting...\n");
			return EXIT_FAILURE;
		}

		// Load the file into host memory
		fread(m_rom_buf, sizeof(unsigned char), m_romsz, m_romfile); 

		printf("ROM size: %d bytes\n", (unsigned int) m_romsz);

		m_load_rom(m_rom_buf);
#ifdef UNIX
	}
#endif

	// Initialize Registers
	m_init_registers();

	m_regs.isUnimplemented = false;

	uint8_t prev_pc;

	extern uint8_t m_boperand;
	extern uint16_t m_woperand;

	// Init SDL2
	// SDL_INIT_VIDEO automatically enables SDL2 Events, we can OR SDL_INIT_AUDIO and SDL_INIT_TIMER if needed in the future
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		SDL_Log("Unable to initialize SDL2: %s", SDL_GetError());
        return EXIT_FAILURE;
	}

	// Create a 160 x 144 (px) window
	m_window = SDL_CreateWindow("GameGirl (SDL2)", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
							  320, 288, SDL_WINDOW_SHOWN);

	// Check if Window could be crafted
	if (m_window == NULL)
	{
        printf("Could not create SDL2 Window: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    m_renderer = SDL_CreateRenderer(m_window, -1, 0);

	// Setup the texture trick that'll enable us to display emulator output
	m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, 160, 144);
	
	m_gpu_init();

	while (true)
	{
		prev_pc = PC;

		while (SDL_PollEvent(&m_event))
		{
			if (m_event.type == SDL_QUIT)
			{
				goto exit;
			}
		}


		/*if (PC == 0x45)
		{
			debug = true;
			printf("\033[0;34mJust written $19 @ 0x9910\033[0;0m\n");
			printf("\033[0;33m0x9910 -> 0x%02X\033[0;0m\n", mmu->gb_mmap.vram[0x1910]);
		}

		if (PC >= 0x45 && mmu->gb_mmap.vram[0x1910] != 0x19 && debug == true)
		{
			printf("\033[0;32mPC: 0x%02X -> 0x9910 now reads: 0x%02X\033[0;0m\n", PC, mmu->gb_mmap.vram[0x1910]);
			//exit(1);
		}

		if (PC == 0xE0)
		{
			FILE *f = fopen("bgmap1.bin", "wb");
			
			int x;
			
			for(x = 0x9800; x < 0x9BFF; x++)
			{
				fprintf(f, "%02x ", mmu_read_byte(x));
			}
			fclose(f);

			f = fopen("tiledata.bin", "wb");
			
			for(x = 0x8190; x < 0x8200; x++)
			{
				fprintf(f, "%02x ", mmu_read_byte(x));
			}
			fclose(f);

			exit(1);
		}*/

		if ((m_breakpoint != 0xFFFFFFFF) && PC == m_breakpoint)
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
				while (SDL_PollEvent(&m_event))
				{
					if (m_event.type == SDL_QUIT)
					{
						goto exit;
					}

					if (m_event.type == SDL_KEYDOWN)
					{
						if (m_event.key.keysym.sym == SDLK_RETURN)
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

		}
		else
		{
			/*
				If no debugging is enabled, execute the regular debugger loop
			*/
			// Start fetching & executing instructions
			m_exec();

			// Execute the GPU Subsystem
			m_gpu_step();

			// Execute the Interrupt Subsystem
			m_int_check();
		}
	}

exit:
	// Free MMU data
	mmu_halt();

	SDL_Quit();

	return EXIT_SUCCESS;
}

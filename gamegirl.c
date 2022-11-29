#include <unistd.h>
#include <debugger.h>
#include <gamegirl.h>
#include <mmu.h>
#include <render.h>
#include <cycle.h>
#include <opcodes.h>
#include <interrupts.h>
#include <sys/time.h>
#include <ppu.h>

uintptr_t *m_dmg_ptr;

int main(int argc, char **argv)
{
	m_dmg_t m_dmg;

	m_dmg_ptr = (uintptr_t *) &m_dmg;

	struct timeval t1, t2;

	m_dmg.m_speedhack = false;


	printf("GameGirl - A C-21 Multiplatform Game Boy Emulator\n");

#if defined (__unix__) || defined (__APPLE__)
	if (argc < 2)
	{
		printf("Usage: ./gamegirl [bootrom] [progname]\n");
		printf("Command-line switches:\n");
		return EXIT_FAILURE;
	}
#endif

	// Init MMU
	mmu_init(&m_dmg);

	// Init Address Space
	m_init_address_space(&m_dmg);

#if defined (__unix__) || defined (__APPLE__)
	// Declare a char pointer with the names of the filenames to load
	__attribute__((unused)) const char *m_bootromname = NULL;
	__attribute__((unused)) const char *m_programname = NULL;
#endif

	uint32_t m_breakpoint = 0xFFFFFFFF;

#if defined (__unix__) || defined (__APPLE__)
	for (int m_args = 1; m_args < argc; m_args++)
	{
		if (!strcmp(argv[m_args], "-bootrom"))
		{
			if ((strstr(argv[m_args + 1], ".bin") != NULL))
			{
				m_bootromname = argv[m_args + 1];
				printf("BootROM File: %s\n", m_bootromname);
				m_args++;
			}
			else
			{
				printf("BootROM File Extension not Supported!\n");
				printf("Valid Format: .bin\n");
				exit(EXIT_FAILURE);
			}
		}
		else
		if (!strcmp(argv[m_args], "-rom"))
		{
			if ((strstr(argv[m_args + 1], ".gb") != NULL) || (strstr(argv[m_args + 1], ".rom") != NULL))
			{
				m_programname = argv[m_args + 1];
				printf("ROM File: %s\n", m_programname);
				m_args++;
			}
			else
			{
				printf("ROM File Extension not Supported!\n");
				printf("Valid Formats: .gb .rom\n");
				exit(EXIT_FAILURE);
			}
		}
		else
		if (!strcmp(argv[m_args], "-break"))
		{
			if (strstr(argv[m_args + 1], "0x") != NULL)
			{
				m_breakpoint = strtol(argv[m_args + 1], NULL, 0);
				printf("Breakpoint set at: $%02X\n", m_breakpoint);
				m_args++;
			}
			else
			{
				printf("Invalid Breakpoint Declaration!\n");
				printf("Valid example: 0x4213\n");
				exit(EXIT_FAILURE);
			}
		}
		else
		if (!strcmp(argv[m_args], "-speedhack"))
		{
			m_dmg.m_speedhack = true;
			printf("Speed Hack Enabled!\n");
		}
		else
		{
			printf("Unknown argument: %s\n", argv[m_args]);
			exit(EXIT_FAILURE);
		}
	}

	if (m_bootromname)
	{
#endif
		FILE *m_bootrom;

#if defined (__unix__) || defined (__APPLE__)
		m_bootrom = fopen(m_bootromname, "rb");
#endif

#ifdef WIN32
		m_bootrom = fopen("bootrom.bin", "rb");
#endif

		// Check if the file has been opened
		if (m_bootrom == NULL)
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
		m_load_bootrom(&m_dmg, m_bootrom_buf);

		free(m_bootrom_buf);

		m_dmg.m_memory->m_in_bootrom = 1;
#if defined (__unix__) || defined (__APPLE__)
	}
	else
	{
		printf("BootROM-less booting\n");
		m_dmg.m_memory->m_in_bootrom = 0;
	}
#endif

#if defined (__unix__) || defined (__APPLE__)
	if (m_programname)
	{
#endif
		FILE *m_romfile;

#if defined (__unix__) || defined (__APPLE__)
		m_romfile = fopen(m_programname, "rb");
#endif

#ifdef WIN32
		m_romfile = fopen("tetris.gb", "rb");
#endif

		// Check if the file has been opened
		if (m_romfile == NULL)
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

		m_load_rom(&m_dmg, m_rom_buf, m_romsz);

		free(m_rom_buf);

#if defined (__unix__) || defined (__APPLE__)
	}
#endif

	m_ppu_init(&m_dmg);

	// Initialize Registers
	m_init_registers(&m_dmg);

	// Init SDL2
	// SDL_INIT_VIDEO automatically enables SDL2 Events, we can OR SDL_INIT_AUDIO and SDL_INIT_TIMER if needed in the future
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		SDL_Log("Unable to initialize SDL2: %s", SDL_GetError());
        return EXIT_FAILURE;
	}

	// Create a 160 x 144 (px) window
	m_dmg.m_window = SDL_CreateWindow("GameGirl (SDL2)", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
							  320, 288, SDL_WINDOW_SHOWN);

	// Check if Window could be crafted
	if (m_dmg.m_window == NULL)
	{
        printf("Could not create SDL2 Window: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    m_dmg.m_renderer = SDL_CreateRenderer(m_dmg.m_window, -1, 0);

	// Setup the texture trick that'll enable us to display emulator output
	m_dmg.m_texture = SDL_CreateTexture(m_dmg.m_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, 160, 144);
	
	if (m_breakpoint)
	{
		SDL_MinimizeWindow(m_dmg.m_window);
	}

	while (true)
	{
		m_dmg.m_cpu->prev_pc = m_dmg.m_cpu->m_registers->pc;

		while (SDL_PollEvent(&m_dmg.m_event))
		{
			if (m_dmg.m_event.type == SDL_QUIT)
			{
				m_gamegirl_exit(0);
				return EXIT_SUCCESS;
			}
		}

		if (!m_dmg.m_speedhack)
		{
			// Start of operation
			gettimeofday(&t1, NULL);
			
			/*
				Run as many cycles as we possibly can before updating the screen
				This is calculated dividing the Frequency of the GameBoy's CPU
				between the target frames per second (59.7).

				Use 60 frames per second threshold in order to fix emulator stuttering
				issues derived from the natural number division.
			*/
			while (m_dmg.m_cpu->m_cpu_ticks < (4194304 / 60))
			{
				/*			
					If the user has added a breakpoint, check if Program Counter is
					the same as the user-defined memory location

					Else, if no debugging is enabled, execute the regular emulation loop
				*/
				if (m_dmg.m_cpu->m_registers->pc == m_breakpoint)
				{
					m_run_debugger(&m_dmg);
				}

				m_dmg.m_cpu->prev_pc = m_dmg.m_cpu->m_registers->pc;
				
				// Start fetching & executing instructions
				size_t m_cycles = m_exec(&m_dmg);

				// Execute the GPU Subsystem
				m_ppu_step(&m_dmg, m_cycles);

				// Execute the Interrupt Subsystem
				m_interrupt_check(&m_dmg);
			}
			
			// Set CPU Ticks back to 0
			m_dmg.m_cpu->m_cpu_ticks = 0;

			// Set GPU Ticks back to 0
			m_dmg.ppu->m_ticks = 0;

			// End of operation
			gettimeofday(&t2, NULL);

			/*
				Calculate the time diff. (Delta) between the start of the operation
				and end of it, divide by 1000 to convert to microsec.
			*/
			double m_delta = ((double) t2.tv_usec - (double) t1.tv_usec) / 1000;

			// Calculate the time to wait between screen updates to throttle the emulation.
			double m_ttwait = ((59.7 - m_delta) * 100);

			// Ceil the time-to-wait and multiply by 10 so that we satisfy usleep's requirements.
			uint64_t m_sleep = ceil(m_ttwait) * 10;

			// Sleep that time slice
#ifdef CODEQL
			sleep(m_sleep);
#else
			usleep(m_sleep);
#endif

			// Update the SDL Texture only if LCDC's Display Enable Bit is on
			if (m_dmg.ppu->m_lcdc & GPU_CONTROL_DISPLAYENABLE) m_sdl_draw_screen(&m_dmg);
		}
		else
		{
			if (m_dmg.m_cpu->m_registers->pc == m_breakpoint)
			{
				m_run_debugger(&m_dmg);
			}
			
			// Start fetching & executing instructions
			m_exec(&m_dmg);

			// Execute the GPU Subsystem
			m_ppu_step(&m_dmg, m_dmg.m_cpu->m_cpu_ticks);

			// Execute the Interrupt Subsystem
			m_interrupt_check(&m_dmg);
		}
	}
}

void m_gamegirl_exit(int m_unused)
{
	(void) m_unused;

	// Free MMU data
	mmu_halt((m_dmg_t *) m_dmg_ptr);

	m_dmg_t *m_dmg = (m_dmg_t *) m_dmg_ptr;

	SDL_Quit();

	if (m_dmg->m_cpu->m_registers != NULL)
		free(m_dmg->m_cpu->m_registers);

	if (m_dmg->m_cpu->interrupts != NULL)
		free(m_dmg->m_cpu->interrupts);
	
	if (m_dmg->ppu != NULL)
		free(m_dmg->ppu);

	if (m_dmg->m_cpu != NULL)
		free(m_dmg->m_cpu);

	exit(1);
}
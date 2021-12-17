#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <GL/gl.h>
#include <gamegirl.h>
#include <mmu.h>
#include <cycle.h>
#include <opcodes.h>
#include <interrupts.h>
#include <sys/time.h>
#include <ppu.h>

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

uint8_t prev_pc;

struct timeval t1, t2;

extern uint64_t m_cpu_ticks;

unsigned int frames;
bool m_speedhack;

int main(int argc, char **argv)
{
	printf("GameGirl - A C-21 Multiplatform Game Boy Emulator\n");

#ifdef __unix__
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

#ifdef __unix__
	// Declare a char pointer with the names of the filenames to load
	[[maybe_unused]] const char *m_bootromname = NULL;
	[[maybe_unused]] const char *m_programname = NULL;
#endif

	uint32_t m_breakpoint = 0xFFFFFFFF;

#ifdef __unix__
	for (size_t m_args = 1; m_args < argc; m_args++)
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
			m_speedhack = true;
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

#ifdef __unix__
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
		m_load_bootrom(m_bootrom_buf);

		mmu->m_in_bootrom = 1;
#ifdef __unix__
	}
	else
	{
		printf("BootROM-less booting\n");
		mmu->m_in_bootrom = 0;
	}
#endif

#ifdef __unix__
	if (m_programname)
	{
#endif
		FILE *m_romfile;

#ifdef __unix__
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

		m_load_rom(m_rom_buf, m_romsz);
#ifdef __unix__
	}
#endif

	// Initialize Registers
	m_init_registers();

	m_regs.isUnimplemented = false;

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
	
	m_ppu_init();

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

		if (!m_speedhack)
		{
			// Start of operation
			gettimeofday(&t1, NULL);
			
			/*
				Run as many cycles as we possibly can before updating the screen
				This is calculated dividing the Frequency of the GameBoy's CPU
				between the target frames per second (59.7)
			*/
			while (m_cpu_ticks < (4194304 / 59.7))
			{
				/*			
					If the user has added a breakpoint, check if Program Counter is
					the same as the user-defined memory location

					Else, if no debugging is enabled, execute the regular emulation loop
				*/
				if (PC == m_breakpoint)
				{
					m_run_debugger();
				}

				prev_pc = PC;
				
				// Start fetching & executing instructions
				size_t m_cycles = m_exec();

				// Execute the GPU Subsystem
				m_ppu_step(m_cycles);

				// Execute the Interrupt Subsystem
				m_interrupt_check();
			}
			
			// Set CPU Ticks back to 0
			m_cpu_ticks = 0;

			// Set GPU Ticks back to 0
			ppu.m_ticks = 0;

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
			usleep(m_sleep);

			// Update the SDL Texture only if LCDC's Display Enable Bit is on
			if (ppu.m_lcdc & GPU_CONTROL_DISPLAYENABLE) m_sdl_draw_screen();
		}
		else
		{
			// Start fetching & executing instructions
			m_exec();

			// Execute the GPU Subsystem
			m_ppu_step(m_cpu_ticks);

			// Execute the Interrupt Subsystem
			m_interrupt_check();
		}
	}

exit:
	// Free MMU data
	mmu_halt();

	SDL_Quit();

	return EXIT_SUCCESS;
}

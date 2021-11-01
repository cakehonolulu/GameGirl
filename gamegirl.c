#include "include/gamegirl.h"
#include "include/mmu.h"
#include "include/cycle.h"
#include "include/opcodes.h"

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
	const char *m_bootromname = NULL;
	const char *m_programname = NULL;

	bool m_foundbootrom = false;
	bool m_foundprogram = false;

	int breakpoint;

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
				char *p;
				
				long conv = strtol(argv[2], &p, 10);
				
				breakpoint = conv;

				printf("%d\n", breakpoint);

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
	m_init_registers(m_regs);

	m_regs.isUnimplemented = false;

	while (true)
	{
		// Start fetching & executing instructions
		m_exec(m_regs);

		if (PC == breakpoint)
		{
			printf("\e[1;1H\e[2J");
			printf("\033[1;32mEntered Debugging Step Mode!\033[0;0m\n");
			extern uint8_t m_opcode;

			uint8_t m_dbgopc = mmu_read_byte(PC);

			m_printregs(m_regs);

			printf("\nLegend: \033[0;34mPrevious Instruction\033[0;0m, \033[0;33mCurrent Instruction\033[0;0m\n\n");

			uint8_t prev_pc = PC - 1;
			uint8_t curr_instr;

			printf("\033[0;34m00:%04X  %02X ->\033[0;0m %s\n", prev_pc, mmu_read_byte(prev_pc), m_gb_instr[m_opcode].m_instr);
			printf("\033[0;33m00:%04X  %02X ->\033[0;0m %s\n\n", PC, mmu_read_byte(PC), m_gb_instr[m_dbgopc].m_instr);

			printf("Press Enter to Step...\n");

			while (true)
			{
				while (getchar())
				{
					printf("\e[1;1H\e[2J");

					uint8_t prev_pc = PC;

					m_exec(m_regs);
					m_printregs(m_regs);

					extern uint8_t m_opcode;

					printf("Legend: \033[0;34mPrevious Instruction\033[0;0m, \033[0;33mCurrent Instruction\033[0;0m\n\n");

					uint8_t m_dbgopc = mmu_read_byte(PC);

					
					printf("\033[0;34m00:%04X  %02X ->\033[0;0m %s\n", prev_pc, mmu_read_byte(prev_pc), m_gb_instr[m_opcode].m_instr);
					printf("\033[0;33m00:%04X  %02X ->\033[0;0m %s\n\n", PC, mmu_read_byte(PC), m_gb_instr[m_dbgopc].m_instr);
					
					printf("Press Enter to Step...\n");
				}
			}
		}

	}

	// Free MMU data
	mmu_halt();

	return EXIT_SUCCESS;
}

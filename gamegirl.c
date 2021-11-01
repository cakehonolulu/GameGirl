#include "include/gamegirl.h"
#include "include/mmu.h"
#include "include/cycle.h"

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
				printf("No more than 1 BootROM file is allowed, exiting...\n");
				exit(EXIT_FAILURE);
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

	memset(mmu->gb_mmap.cart, 0, sizeof(mmu->gb_mmap.cart));

	// Load Bootrom
	m_load_bootrom(m_bootrom_buf);

	// Initialize Registers
	m_init_registers(m_regs);

	m_regs.isUnimplemented = false;

	while (true)
	{
		// Start fetching & executing instructions
		m_exec(m_regs);
	}

	// Free MMU data
	mmu_halt();

	return EXIT_SUCCESS;
}

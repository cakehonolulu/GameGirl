#include "includes/gamegirl.h"
#include "includes/mmu.h"

int main(int argc, char **argv)
{
	printf("GameGirl - A C-21 Multiplatform Game Boy Emulator\n");

	// Declare a new MMU
	gb_mmu_t mmu;

	if (sizeof(mmu.gb_mmap) != GB_ADDRSPC_SIZE)
	{
		printf("MMU Size: 0x%lx\n", sizeof(mmu.gb_mmap));
	} else {
		printf("MMU Size not correct, expected 0x10000 got 0x%lu instead! Exiting...\n", sizeof(mmu.gb_mmap));
		return EXIT_FAILURE;
	}
	
}
#include "includes/gamegirl.h"
#include "includes/mmu.h"

int main(int argc, char **argv)
{
	printf("GameGirl - A C-21 Multiplatform Game Boy Emulator\n");

	// Init MMU
	gb_mmu_t *mmu = mmu_init();

	// Load Bootrom
	m_load_bootrom(mmu);

	uint8_t opcode = mmu_read_addr8(mmu, 0x0000);

	mmu_halt(mmu);

	return EXIT_SUCCESS;
}
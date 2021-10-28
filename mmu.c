#include "includes/mmu.h"
#include "includes/gamegirl.h"

gb_mmu_t *mmu_init()
{
	// Allocate a new MMU
	gb_mmu_t *gb_mmu = (gb_mmu_t*)malloc(sizeof(gb_mmu_t));

	// Check if malloc() succeeded
	if (!gb_mmu)
	{
		printf("\033[0;31mMMU Structure can't be allocated, exiting...\033[0;37m");
		exit(EXIT_FAILURE);
	}

	// Check if the size of the MMAP equals to the GameBoy's Address Space
	if (sizeof(gb_mmu->gb_mmap) != GB_ADDRSPC_SIZE)
	{
		printf("MMU Size: 0x%lx\n", sizeof(gb_mmu->gb_mmap));
	} else {
		printf("\033[0;31mMMU Size not correct, expected 0x10000 got 0x%lu instead! Exiting...\033[0;37m\n",
		 sizeof(gb_mmu->gb_mmap));

		// Exit if we exceed or cut short on MMAP space
		exit(EXIT_FAILURE);
	}

	// Set the bootrom end at $FF50
	gb_mmu->gb_bootrom_end = gb_mmu->gb_address_space + 0xFF50;

	return gb_mmu;
}

void mmu_halt(gb_mmu_t *gb_mmu)
{
	if (!gb_mmu)
	{
		printf("MMU not found, exiting...\n");
		exit(EXIT_FAILURE);
	}

	free(gb_mmu);
	gb_mmu = NULL;
}

uint8_t mmu_read_addr8(gb_mmu_t *gb_mmu, uint16_t m_addr)
{
	if (!(*gb_mmu->gb_bootrom_end) && m_addr >= 0x00 && m_addr <= 0xFF)
		return gb_mmu->gb_bootrom[m_addr];
	
	return *(gb_mmu->gb_address_space + m_addr);
}

void mmu_write_addr8(gb_mmu_t *gb_mmu, uint16_t m_addr, uint8_t m_data)
{	
	gb_mmu->gb_address_space[m_addr] = m_data;
}

uint16_t mmu_read_addr16(gb_mmu_t *gb_mmu, uint16_t m_addr)
{
	if (!(*gb_mmu->gb_bootrom_end) && m_addr >= 0x00 && m_addr <= 0xFF)
		return *((uint16_t*)(gb_mmu->gb_bootrom + m_addr));
	
	return *((uint16_t*)(gb_mmu->gb_address_space + m_addr));
}

void mmu_write_addr16(gb_mmu_t *gb_mmu, uint16_t m_addr, uint16_t m_data)
{
	uint16_t *m_pos = ((uint16_t*)(gb_mmu->gb_address_space + m_addr));
	*m_pos = m_data;
}

void mmu_load_bios(gb_mmu_t *gb_mmu)
{
	memcpy((void*)gb_mmu->gb_bootrom, (const void*)GB_BIOS, sizeof(GB_BIOS));
	(*gb_mmu->gb_bootrom_end) = false;
}
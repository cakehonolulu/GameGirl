#include "includes/mmu.h"
#include "includes/gamegirl.h"

gb_mmu_t *mmu_init()
{
	gb_mmu_t *gb_mmu = (gb_mmu_t*)malloc(sizeof(gb_mmu_t));

	if (sizeof(gb_mmu.gb_mmap) != GB_ADDRSPC_SIZE)
	{
		printf("MMU Size: 0x%lx\n", sizeof(gb_mmu.gb_mmap));
	} else {
		printf("MMU Size not correct, expected 0x10000 got 0x%lu instead! Exiting...\n", sizeof(mmu.gb_mmap));
		return EXIT_FAILURE;
	}
	
	gb_mmu->gb_bootrom_end = gb_mmu->gb_address_space + 0xFF50;

	return gb_mmu;
}

void mmu_halt(gb_mmu_t *gb_mmu)
{
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

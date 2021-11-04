#include "include/mmu.h"
#include "include/gamegirl.h"
#include "include/gpu.h"
#include "include/int.h"
#include <limits.h>

gb_mmu_t *mmu_init()
{
	// Allocate a new MMU
	gb_mmu_t *mmu = (gb_mmu_t*)malloc(sizeof(gb_mmu_t));

	// Check if malloc() succeeded
	if (!mmu)
	{
		printf("\033[0;31mMMU Structure can't be allocated, exiting...\033[0;37m");
		exit(EXIT_FAILURE);
	}

	// Check if the size of the MMAP equals to the GameBoy's Address Space
	if (sizeof(mmu->gb_mmap) != GB_ADDRSPC_SIZE)
	{
		printf("MMU Size: 0x%lx\n", sizeof(mmu->gb_mmap));
	} else {
		printf("\033[0;31mMMU Size not correct, expected 0x10000 got 0x%lu instead! Exiting...\033[0;37m\n",
		 sizeof(mmu->gb_mmap));

		// Exit if we exceed or cut short on MMAP space
		exit(EXIT_FAILURE);
	}

	return mmu;
}

void mmu_halt()
{
	if (!mmu)
	{
		printf("MMU not found, exiting...\n");
		exit(EXIT_FAILURE);
	}

	free(mmu);
	mmu = NULL;
}

// Unsafe Option (DMA, no MMU Processing at all)
uint8_t mmu_read_addr8(uint16_t m_addr)
{
#pragma GCC diagnostic ignored "-Wtype-limits"
	if (m_addr >= 0x00 && m_addr <= UCHAR_MAX)
    {
		return mmu->gb_bootrom[m_addr];
    }
#pragma GCC diagnostic pop
    
	return *(mmu->gb_address_space + m_addr);
}

// Unsafe Option (DMA, no MMU Processing at all)
void mmu_write_addr8(uint16_t m_addr, uint8_t m_data)
{	
	mmu->gb_address_space[m_addr] = m_data;
}

// Unsafe Option (DMA, no MMU Processing at all)
uint16_t mmu_read_addr16(uint16_t m_addr)
{
#pragma GCC diagnostic ignored "-Wtype-limits"
	if (m_addr >= 0x00 && m_addr <= UCHAR_MAX)
    {
		return *((uint16_t*)(mmu->gb_bootrom + m_addr));
    }
#pragma GCC diagnostic pop

	return *((uint16_t*)(mmu->gb_address_space + m_addr));
}

// Unsafe Option (DMA, no MMU Processing at all)
void mmu_write_addr16(uint16_t m_addr, uint16_t m_data)
{
	uint16_t *m_pos = ((uint16_t*)(mmu->gb_address_space + m_addr));
	*m_pos = m_data;
}

// Safe Option, goes through MMU
uint8_t mmu_read_byte(uint16_t m_addr)
{
#pragma GCC diagnostic ignored "-Wtype-limits"
    if (m_addr >= 0x00 && m_addr <= UCHAR_MAX)
    {
        return mmu->gb_bootrom[m_addr];
    }
#pragma GCC diagnostic pop

    // #0 Cart (Fixed) [0x0 - 0x3FFF]
    if (m_addr >= 0x0000 && 0x3FFF >= m_addr)
    {
        return mmu->gb_mmap.cart[m_addr];
    }
    else if (m_addr >= 0x4000 && 0x7FFF >= m_addr)          // #1 Cart (Switchable) [0x4000 - 0x7FFF]
    {
        return mmu->gb_mmap.cart_sw[m_addr - 0x4000];
    }
    else if (m_addr >= 0x8000 && 0x9FFF >= m_addr)          // VRAM [0x8000 - 0x9FFF]
    {
        return mmu->gb_mmap.vram[m_addr - 0x8000];
    }
    else if (m_addr >= 0xA000 && 0xBFFF >= m_addr)          // Cartridge RAM (If Exists) [0xA000 - 0xBFFF]
    {
        return mmu->gb_mmap.cart_ram[m_addr - 0xA000];
    }
    else if (m_addr >= 0xC000 && 0xDFFF >= m_addr)          // Working RAM [0xC000 - 0xDFFF]
    {
        return mmu->gb_mmap.wram[m_addr - 0xC000];
    }
    else if (m_addr >= 0xE000 && 0xFDFF >= m_addr)          // Shadow of the Working RAM (Due to PCB layout)
    {
        return mmu->gb_mmap.wram[m_addr - 0xE000];
    }
    else if (m_addr >= 0xFE00 && 0xFEFF >= m_addr)
    {
        return mmu->gb_mmap.oam[m_addr - 0xFE00];
    }
    else if (m_addr == 0xFF00)
    {
        // GameBoy Key Handling
    }
    else if (m_addr == 0xFF04)
    {
        // IOREG Handling
    }
    else if (m_addr == 0xFF05)
    {
        // IOREG Handling
    }
    else if (m_addr == 0xFF06)
    {
        // IOREG Handling
    }
    else if (m_addr == 0xFF0F)
    {
        return mmu->gb_mmap.hw_io_reg[0x0F];
    }
    else if (m_addr == 0xFF40)
    {
        return gpu.m_config;
    }
    else if (m_addr == 0xFF42)
    {
        return gpu.m_verticalscroll;
    }
    else if (m_addr == 0xFF43)
    {
        return gpu.m_horitzontalscroll;
    }
    else if (m_addr == 0xFF44)
    {
        return gpu.m_scanline;
    }
    else if (m_addr >= 0xFF00 && 0xFF7F >= m_addr)
    {
        return mmu->gb_mmap.hw_io_reg[m_addr - 0xFF00];
    }
    else if (m_addr >= 0xFF80 && 0xFFFE >= m_addr) 
    {
        return mmu->gb_mmap.zram[m_addr - 0xFF80];
    }
    else if (m_addr == 0xFFFF)
    {
        return ints.m_enabled;
    }

    return 0;

}

// Safe Option, goes through MMU
uint8_t mmu_write_byte(uint16_t m_addr, uint8_t m_data)
{
#pragma GCC diagnostic ignored "-Wtype-limits"
    if (m_addr >= 0x00 && m_addr <= UCHAR_MAX)
    {
        return 0;
    }
#pragma GCC diagnostic pop

    // #0 Cart (Fixed) [0x0 - 0x3FFF]
    if (m_addr >= 0x0000 && 0x3FFF >= m_addr)
    {
        return mmu->gb_mmap.cart[m_addr] = m_data;
    }
    else if (m_addr >= 0x4000 && 0x7FFF >= m_addr)          // #1 Cart (Switchable) [0x4000 - 0x7FFF]
    {
        return mmu->gb_mmap.cart_sw[m_addr - 0x4000] = m_data;
    }
    else if (m_addr >= 0x8000 && 0x9FFF >= m_addr)          // VRAM [0x8000 - 0x9FFF]
    {
        return mmu->gb_mmap.vram[m_addr - 0x8000] = m_data;
    }
    else if (m_addr >= 0xA000 && 0xBFFF >= m_addr)          // Cartridge RAM (If Exists) [0xA000 - 0xBFFF]
    {
        return mmu->gb_mmap.cart_ram[m_addr - 0xA000] = m_data;
    }
    else if (m_addr >= 0xC000 && 0xDFFF >= m_addr)          // Working RAM [0xC000 - 0xDFFF]
    {
        return mmu->gb_mmap.wram[m_addr - 0xC000] = m_data;
    }
    else if (m_addr >= 0xE000 && 0xFDFF >= m_addr)          // Shadow of the Working RAM (Due to PCB layout)
    {
        return mmu->gb_mmap.wram[m_addr - 0xE000] = m_data;
    }
    else if (m_addr >= 0xFE00 && 0xFEFF >= m_addr)
    {
        return mmu->gb_mmap.oam[m_addr - 0xFE00] = m_data;
    }
    else if (m_addr == 0xFF04)
    {
        // IOREG Handling
    }
    else if (m_addr == 0xFF05)
    {
        // IOREG Handling
    }
    else if (m_addr == 0xFF06)
    {
        // IOREG Handling
    }
    else if (m_addr == 0xFF40)
    {
        // LCD Handling
    }
    else if (m_addr == 0xFF41)
    {
        return gpu.m_config = m_data;
    }
    else if (m_addr == 0xFF42)
    {
        return gpu.m_horitzontalscroll = m_data;
    }
    else if (m_addr == 0xFF43)
    {
        return gpu.m_verticalscroll = m_data;
    }
    else if(m_addr == 0xff46)
    {
        // OAM Handling
    }
    else if (m_addr == 0xFF47)
    {
        // Graphics Handling
    }
    else if (m_addr == 0xFF48)
    {
        // Graphics Handling
    }
    else if (m_addr == 0xFF49) 
    {
        // Graphics Handling
    }
    else if (m_addr == 0xFF4A)
    {
        // Graphics Handling
    }
    else if (m_addr == 0xFF4B)
    {
        // Graphics Handling
    }
    else if (m_addr == 0xFF00)
    {
        // Key Handling
    }
    else if (m_addr >= 0xFF00 && 0xFF7F >= m_addr)
    {
        return mmu->gb_mmap.hw_io_reg[m_addr - 0xFF00] = m_data;
    }
    else if (m_addr >= 0xFF80 && 0xFFFE >= m_addr) 
    {
        return mmu->gb_mmap.zram[m_addr - 0xFF80] = m_data;
    }
    else if (m_addr == 0xFF0F)
    {
        return ints.m_flags = m_data;
    }
    else if (m_addr == 0xFFFF)
    {
        return ints.m_enabled = m_data;
    }

    return 0;
}

uint16_t mmu_read_word(uint16_t m_addr)
{
    return (mmu_read_byte(m_addr) | (mmu_read_byte(m_addr + 1) << 8));
}

uint8_t mmu_write_word(uint16_t m_addr, uint16_t m_data)
{
    return (uint8_t) mmu_write_byte(m_addr, m_data & 0xFF) & mmu_write_byte(m_addr + 1, m_data >> 8);
}

void m_load_bootrom(unsigned char *m_bootrom)
{
	memcpy((void*)mmu->gb_bootrom, (const void*)m_bootrom, GB_BOOTROM_SZ);

#ifdef OPCODE_DEBUG
	printf("BootROM Dump:\n");
	for (size_t i = 0; i < GB_BOOTROM_SZ; i++)
	{
		printf("0x%x ", mmu->gb_mmap.cart[i]);
	}
	printf("\n");
#endif
}

void m_init_address_space()
{
    // Clear Cart 0
    memset(mmu->gb_mmap.cart, 0, sizeof(mmu->gb_mmap.cart));

    // Clear VRAM
    memset(mmu->gb_mmap.vram, 0, sizeof(mmu->gb_mmap.vram));

    // Clear Cartridge RAM
    memset(mmu->gb_mmap.cart_ram, 'F', sizeof(mmu->gb_mmap.cart_ram));

    // Clear WRAM
    memset(mmu->gb_mmap.wram, 0, sizeof(mmu->gb_mmap.wram));

    // Clear OAM
    memset(mmu->gb_mmap.oam, 0, sizeof(mmu->gb_mmap.oam));
}
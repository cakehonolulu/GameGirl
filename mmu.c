#include <mmu.h>
#include <gamegirl.h>
#include <ppu.h>
#include <interrupts.h>
#include <limits.h>

void mmu_init(m_dmg_t *m_dmg)
{
	// Allocate a new MMU
	m_dmg->m_memory = (gb_mmu_t*) malloc(sizeof(gb_mmu_t));

	// Check if malloc() succeeded
	if (!m_dmg->m_memory)
	{
		printf("\033[0;31mMMU Structure can't be allocated, exiting...\033[0;37m");
		exit(EXIT_FAILURE);
	}

	// Check if the size of the MMAP equals to the GameBoy's Address Space
	if (sizeof(m_dmg->m_memory->gb_mmap) != GB_ADDRSPC_SIZE)
	{
		printf("MMU Size: 0x%lx\n", sizeof(m_dmg->m_memory->gb_mmap));
	} else {
		printf("\033[0;31mMMU Size not correct, expected 0x10000 got 0x%lu instead! Exiting...\033[0;37m\n",
		 sizeof(m_dmg->m_memory->gb_mmap));

		// Exit if we exceed or cut short on MMAP space
		exit(EXIT_FAILURE);
	}
}

void mmu_halt(m_dmg_t *m_dmg)
{
	if (!m_dmg->m_memory)
	{
		printf("MMU not found, exiting...\n");
		exit(EXIT_FAILURE);
	}

	free(m_dmg->m_memory);
}

// Unsafe Option (DMA, no MMU Processing at all)
__attribute__((deprecated("Unsafe Option, use mmu_read_byte"))) uint8_t mmu_read_addr8(m_dmg_t *m_dmg, uint16_t m_addr)
{
#pragma GCC diagnostic push "-Wtype-limits"
	if (m_addr >= 0x00 && m_addr <= UCHAR_MAX)
    {
		return m_dmg->m_memory->gb_bootrom[m_addr];
    }
#pragma GCC diagnostic pop
    
	return *(m_dmg->m_memory->gb_address_space + m_addr);
}

// Unsafe Option (DMA, no MMU Processing at all)
__attribute__((deprecated("Unsafe Option, use mmu_write_byte"))) void mmu_write_addr8(m_dmg_t *m_dmg, uint16_t m_addr, uint8_t m_data)
{	
	m_dmg->m_memory->gb_address_space[m_addr] = m_data;
}

// Unsafe Option (DMA, no MMU Processing at all)
__attribute__((deprecated("Unsafe Option, use mmu_read_byte"))) uint16_t mmu_read_addr16(m_dmg_t *m_dmg, uint16_t m_addr)
{
#pragma GCC diagnostic push "-Wtype-limits"
	if (m_addr >= 0x00 && m_addr <= UCHAR_MAX)
    {
		return *((uint16_t*)(m_dmg->m_memory->gb_bootrom + m_addr));
    }
#pragma GCC diagnostic pop

	return *((uint16_t*)(m_dmg->m_memory->gb_address_space + m_addr));
}

// Unsafe Option (DMA, no MMU Processing at all)
__attribute__((deprecated("Unsafe Option, use mmu_write_byte"))) void mmu_write_addr16(m_dmg_t *m_dmg, uint16_t m_addr, uint16_t m_data)
{
	uint16_t *m_pos = ((uint16_t*)(m_dmg->m_memory->gb_address_space + m_addr));
	*m_pos = m_data;
}

// Safe Option, goes through MMU
uint8_t mmu_read_byte(m_dmg_t *m_dmg, uint16_t m_addr)
{
#pragma GCC diagnostic push "-Wtype-limits"
    // While on BootROM, 0x00 -> 0xFF are R/O
    if (m_dmg->m_memory->m_in_bootrom && m_addr >= 0x00 && m_addr <= 0xFF)
        return m_dmg->m_memory->gb_bootrom[m_addr];
#pragma GCC diagnostic pop

    // #0 Cart (Fixed) [0x0 - 0x3FFF]
    if (m_addr >= 0x0000 && 0x3FFF >= m_addr)
    {
        return m_dmg->m_memory->gb_mmap.cart[m_addr];
    }
    else if (m_addr >= 0x4000 && 0x7FFF >= m_addr)          // #1 Cart (Switchable) [0x4000 - 0x7FFF]
    {
        return m_dmg->m_memory->gb_mmap.cart_sw[m_addr - 0x4000];
    }
    else if (m_addr >= 0x8000 && 0x9FFF >= m_addr)          // VRAM [0x8000 - 0x9FFF]
    {
        return m_dmg->m_memory->gb_mmap.vram[m_addr - 0x8000];
    }
    else if (m_addr >= 0xA000 && 0xBFFF >= m_addr)          // Cartridge RAM (If Exists) [0xA000 - 0xBFFF]
    {
        return m_dmg->m_memory->gb_mmap.cart_ram[m_addr - 0xA000];
    }
    else if (m_addr >= 0xC000 && 0xDFFF >= m_addr)          // Working RAM [0xC000 - 0xDFFF]
    {
        return m_dmg->m_memory->gb_mmap.wram[m_addr - 0xC000];
    }
    else if (m_addr >= 0xE000 && 0xFDFF >= m_addr)          // Shadow of the Working RAM (Due to PCB layout)
    {
        return m_dmg->m_memory->gb_mmap.wram[m_addr - 0xE000];
    }
    else if (m_addr >= 0xFE00 && 0xFEFF >= m_addr)
    {
        return m_dmg->m_memory->gb_mmap.oam[m_addr - 0xFE00];
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
        return m_dmg->m_cpu->interrupts->m_flags;
    }
    else if (m_addr == 0xFF40)
    {
        return m_dmg->ppu->m_lcdc;
    }
    else if (m_addr == 0xFF41)
    {
        return m_dmg->ppu->m_stat;
    }
    else if (m_addr == 0xFF42)
    {
        return m_dmg->ppu->m_verticalscroll;
    }
    else if (m_addr == 0xFF43)
    {
        return m_dmg->ppu->m_horitzontalscroll;
    }
    else if (m_addr == 0xFF44)
    {
        return m_dmg->ppu->m_scanline;
    }
    else if (m_addr >= 0xFF00 && 0xFF7F >= m_addr)
    {
        return m_dmg->m_memory->gb_mmap.hw_io_reg[m_addr - 0xFF00];
    }
    else if (m_addr >= 0xFF80 && 0xFFFE >= m_addr) 
    {
        return m_dmg->m_memory->gb_mmap.zram[m_addr - 0xFF80];
    }
    else if (m_addr == 0xFFFF)
    {
        return m_dmg->m_cpu->interrupts->m_enabled;
    }

    return 0;

}

int i = 0;

// Safe Option, goes through MMU
uint8_t mmu_write_byte(m_dmg_t *m_dmg, uint16_t m_addr, uint8_t m_data)
{
#pragma GCC diagnostic push "-Wtype-limits"
    // While on BootROM, 0x00 -> 0xFF are R/O
    if (m_dmg->m_memory->m_in_bootrom && m_addr >= 0x00 && m_addr <= 0xFF)
        return 0;
#pragma GCC diagnostic pop

    // #0 Cart (Fixed) [0x0 - 0x3FFF]
    if (m_addr >= 0x0000 && 0x3FFF >= m_addr)
    {
        return m_dmg->m_memory->gb_mmap.cart[m_addr] = m_data;
    }
    else if (m_addr >= 0x4000 && 0x7FFF >= m_addr)          // #1 Cart (Switchable) [0x4000 - 0x7FFF]
    {
        return m_dmg->m_memory->gb_mmap.cart_sw[m_addr - 0x4000] = m_data;
    }
    else if (m_addr >= 0x8000 && 0x9FFF >= m_addr)          // VRAM [0x8000 - 0x9FFF]
    {
        m_dmg->m_memory->gb_mmap.vram[m_addr - 0x8000] = m_data;
        
        if(m_addr <= 0x97FF)
        {
            m_ppu_update_tile(m_dmg, m_addr);
        }
    }
    else if (m_addr >= 0xA000 && 0xBFFF >= m_addr)          // Cartridge RAM (If Exists) [0xA000 - 0xBFFF]
    {
        return m_dmg->m_memory->gb_mmap.cart_ram[m_addr - 0xA000] = m_data;
    }
    else if (m_addr >= 0xC000 && 0xDFFF >= m_addr)          // Working RAM [0xC000 - 0xDFFF]
    {
        return m_dmg->m_memory->gb_mmap.wram[m_addr - 0xC000] = m_data;
    }
    else if (m_addr >= 0xE000 && 0xFDFF >= m_addr)          // Shadow of the Working RAM (Due to PCB layout)
    {
        return m_dmg->m_memory->gb_mmap.wram[m_addr - 0xE000] = m_data;
    }
    else if (m_addr >= 0xFE00 && 0xFEFF >= m_addr)
    {
        return m_dmg->m_memory->gb_mmap.oam[m_addr - 0xFE00] = m_data;
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
        return m_dmg->ppu->m_lcdc = m_data;
    }
    else if (m_addr == 0xFF41)
    {
        return m_dmg->ppu->m_stat = m_data;
    }
    else if (m_addr == 0xFF42)
    {
        return m_dmg->ppu->m_verticalscroll = m_data;
    }
    else if (m_addr == 0xFF43)
    {
        return m_dmg->ppu->m_horitzontalscroll = m_data;
    }
    else if(m_addr == 0xff46)
    {
        // OAM Handling
    }
    else if (m_addr == 0xFF47)
    {
        m_ppu_update_palette(m_dmg, m_data);
        return m_dmg->ppu->m_palette = m_data; // write only
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
        return m_dmg->m_memory->gb_mmap.hw_io_reg[m_addr - 0xFF00] = m_data;
    }
    else if (m_addr >= 0xFF80 && 0xFFFE >= m_addr) 
    {
        return m_dmg->m_memory->gb_mmap.zram[m_addr - 0xFF80] = m_data;
    }
    else if (m_addr == 0xFF0F)
    {
        return m_dmg->m_cpu->interrupts->m_flags = m_data;
    }
    else if (m_addr == 0xFFFF)
    {
        return m_dmg->m_cpu->interrupts->m_enabled = m_data;
    }

    return 0;
}

uint16_t mmu_read_word(m_dmg_t *m_dmg, uint16_t m_addr)
{
    return ((mmu_read_byte(m_dmg, m_addr) << 8) | (mmu_read_byte(m_dmg, m_addr + 1)));
}

uint8_t mmu_write_word(m_dmg_t *m_dmg, uint16_t m_addr, uint16_t m_data)
{
    return (uint8_t) mmu_write_byte(m_dmg, m_addr, m_data >> 8) & mmu_write_byte(m_dmg, m_addr + 1, m_data & 0xFF);
}

void m_load_bootrom(m_dmg_t *m_dmg, unsigned char *m_bootrom)
{
	memcpy((void*)m_dmg->m_memory->gb_bootrom, (const void*)m_bootrom, GB_BOOTROM_SZ);

#ifdef OPCODE_DEBUG
	printf("BootROM Dump:\n");
	for (size_t i = 0; i < GB_BOOTROM_SZ; i++)
	{
		printf("0x%x ", m_dmg->m_memory->gb_bootrom[i]);
	}
	printf("\n");
#endif

    // Map the BootROM (Unmapped 0x0, Mapped 0x1)
    m_dmg->m_memory->m_in_bootrom = 1;
}

void m_init_address_space(m_dmg_t *m_dmg)
{
    // Clear Cart 0
    memset(m_dmg->m_memory->gb_mmap.cart, 0xFF, sizeof(m_dmg->m_memory->gb_mmap.cart));

    // Clear VRAM
    memset(m_dmg->m_memory->gb_mmap.vram, 0, sizeof(m_dmg->m_memory->gb_mmap.vram));

    // Clear Cartridge RAM
    memset(m_dmg->m_memory->gb_mmap.cart_ram, 'F', sizeof(m_dmg->m_memory->gb_mmap.cart_ram));

    // Clear WRAM
    memset(m_dmg->m_memory->gb_mmap.wram, 0, sizeof(m_dmg->m_memory->gb_mmap.wram));

    // Clear OAM
    memset(m_dmg->m_memory->gb_mmap.oam, 0, sizeof(m_dmg->m_memory->gb_mmap.oam));
}

void m_load_rom(m_dmg_t *m_dmg, unsigned char *m_rom, size_t m_rom_sz)
{
    memcpy((void*)m_dmg->m_memory->gb_mmap.cart, (const void*)m_rom, m_rom_sz);
}

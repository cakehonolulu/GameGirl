#include "include/mmu.h"
#include "include/gamegirl.h"

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

// Unsafe Option (DMA, no MMU Processing at all)
uint8_t mmu_read_addr8(gb_mmu_t *gb_mmu, uint16_t m_addr)
{
	if (m_addr >= 0x00 && m_addr <= 0xFF)
		return gb_mmu->gb_bootrom[m_addr];
	
	return *(gb_mmu->gb_address_space + m_addr);
}

// Unsafe Option (DMA, no MMU Processing at all)
void mmu_write_addr8(gb_mmu_t *gb_mmu, uint16_t m_addr, uint8_t m_data)
{	
	gb_mmu->gb_address_space[m_addr] = m_data;
}

// Unsafe Option (DMA, no MMU Processing at all)
uint16_t mmu_read_addr16(gb_mmu_t *gb_mmu, uint16_t m_addr)
{
	if (m_addr >= 0x00 && m_addr <= 0xFF)
		return *((uint16_t*)(gb_mmu->gb_bootrom + m_addr));
	
	return *((uint16_t*)(gb_mmu->gb_address_space + m_addr));
}

// Unsafe Option (DMA, no MMU Processing at all)
void mmu_write_addr16(gb_mmu_t *gb_mmu, uint16_t m_addr, uint16_t m_data)
{
	uint16_t *m_pos = ((uint16_t*)(gb_mmu->gb_address_space + m_addr));
	*m_pos = m_data;
}

// Safe Option, goes through MMU
uint8_t mmu_read_byte(gb_mmu_t *gb_mmu, uint16_t m_addr)
{
    if (m_addr >= 0x00 && m_addr <= 0xFF)
        return gb_mmu->gb_bootrom[m_addr];

    switch ((m_addr & 0xF000) >> 12)
    {
    	// #0 Cart (Fixed) [0x0 - 0x3FFF]
    	case 0x0: case 0x1: case 0x2: case 0x3:
    		return gb_mmu->gb_mmap.cart[m_addr];

    	// #1 Cart (Switchable) [0x4000 - 0x7FFF]
    	case 0x4: case 0x5: case 0x6: case 0x7:
    		return gb_mmu->gb_mmap.cart_sw[m_addr - 0x4000];

    	// VRAM [0x8000 - 0x9FFF]
    	case 0x8: case 0x9:
    		return gb_mmu->gb_mmap.vram[m_addr - 0x8000];

    	// Cartridge RAM (If Exists) [0xA000 - 0xBFFF]
    	case 0xA: case 0xB:
    		return gb_mmu->gb_mmap.cart_ram[m_addr - 0xA000];

    	// Working RAM
    	case 0xC: case 0xD:
    		return gb_mmu->gb_mmap.wram[m_addr - 0xC000];

    	// Shadow of the Working RAM (Due to PCB layout)
    	case 0xE:
    		return gb_mmu->gb_mmap.wram[m_addr - 0xC000];

    	case 0xF:
    		/*
    			To cover the last bytes of memory (0xF000 - 0xFFFF)
    			we need to use a switch statement and check for
    			each second digit of the address to decide where
    			to route the read to
    		*/
    		// Adding 0x0F00 acomplishes exactly that
    		switch(m_addr & 0x0F00)
    		{
 				// Shadow of the Working RAM
                case 0x000: case 0x100: case 0x200: case 0x300:
                case 0x400: case 0x500: case 0x600: case 0x700:
                case 0x800: case 0x900: case 0xA00: case 0xB00:
                case 0xC00: case 0xD00:
                    return gb_mmu->gb_mmap.wram[m_addr - 0x1FFF];

                // Sprite information
                case 0xE00:
                    if (m_addr < 0xFEA0)
                        return gb_mmu->gb_mmap.oam[m_addr & 0xFF];
                    else
                        return 0;

                case 0xF00:
                	// Check if it's reading from intenable region (Last byte)
                    if (m_addr == 0xFFFF)
                    	// Interrupt Enable
                        return gb_mmu->gb_mmap.intenable;
                    else
                    {
                    	/*
                    		We'll use another switch statement to decide where the
                    		last tidbits will be routed to, we need the third digit
                    		so we'll add 0x00F0 to m_addr
                    	*/
                        // Memory-mapped IO
                        switch (m_addr & 0x00F0)
                        {
                        	// IO
                            case 0x00:
                                return gb_mmu->gb_mmap.io[m_addr & 0xFF];

                            // PPU
                            case 0x40: case 0x50: case 0x60: case 0x70:
                                return gb_mmu->gb_mmap.ppu[m_addr - 0xFF40];

                            // Zero-Page RAM
                            case 0x80: case 0x90: case 0xA0: case 0xB0:
                            case 0xC0: case 0xD0: case 0xE0: case 0xF0:
                                return gb_mmu->gb_mmap.zram[m_addr & 0x7F];
                        }
                    }

				default:
					break;
			}

    	default:
    		break;
    }
}

// Safe Option, goes through MMU
uint8_t mmu_write_byte(gb_mmu_t *gb_mmu, uint16_t m_addr, uint8_t m_data)
{
    if (m_addr >= 0x00 && m_addr <= 0xFF)
        return 0;

    switch ((m_addr & 0xF000) >> 12)
    {
    	// #0 & #1 Cart (Fixed & Switchable) [0x0 - 0x7FFF] are R/O
    	case 0x0: case 0x1: case 0x2: case 0x3:
    	case 0x4: case 0x5: case 0x6: case 0x7:
    		return 0;

    	// VRAM [0x8000 - 0x9FFF]
    	case 0x8: case 0x9:
    		gb_mmu->gb_mmap.vram[m_addr - 0x8000] = m_data;
    		return 1;

    	// Cartridge RAM (If Exists) [0xA000 - 0xBFFF]
    	case 0xA: case 0xB:
    		gb_mmu->gb_mmap.cart_ram[m_addr - 0xA000] = m_data;
    		return 2;

    	// Working RAM
    	case 0xC: case 0xD:
    		gb_mmu->gb_mmap.wram[m_addr - 0xC000] = m_data;
    		return 3;

    	// Shadow of the Working RAM (Due to PCB layout)
    	case 0xE:
    		gb_mmu->gb_mmap.wram[m_addr - 0xC000] = m_data;
    		return 4;

    	case 0xF:
    		/*
    			To cover the last bytes of memory (0xF000 - 0xFFFF)
    			we need to use a switch statement and check for
    			each second digit of the address to decide where
    			to route the read to
    		*/
    		// Adding 0x0F00 acomplishes exactly that
    		switch(m_addr & 0x0F00)
    		{
 				// Shadow of the Working RAM
                case 0x000: case 0x100: case 0x200: case 0x300:
                case 0x400: case 0x500: case 0x600: case 0x700:
                case 0x800: case 0x900: case 0xA00: case 0xB00:
                case 0xC00: case 0xD00:
                	gb_mmu->gb_mmap.wram[m_addr - 0x1FFF] = m_data;
                    return 4;

                // Sprite information
                case 0xE00:
                    if (m_addr < 0xFEA0)
                    {
                    	gb_mmu->gb_mmap.oam[m_addr & 0xFF] = m_data;
                        return 5;
                    } else {
                        return 0;
                    }

                case 0xF00:
                	// Check if it's reading from intenable region (Last byte)
                    if (m_addr == 0xFFFF)
                    {
                    	// Interrupt Enable
                    	gb_mmu->gb_mmap.intenable[0] = m_data;
                        return 0xA;
                    } else {
                    	/*
                    		We'll use another switch statement to decide where the
                    		last tidbits will be routed to, we need the third digit
                    		so we'll add 0x00F0 to m_addr
                    	*/
                        // Memory-mapped IO
                        switch (m_addr & 0x00F0)
                        {
                        	// IO
                            case 0x00:
                                gb_mmu->gb_mmap.io[m_addr & 0xFF] = m_data;
                                return 6;

                            // PPU
                            case 0x40: case 0x50: case 0x60: case 0x70:
                                gb_mmu->gb_mmap.ppu[m_addr - 0xFF40] = m_data;
                                return 7;

                            // Zero-Page RAM
                            case 0x80: case 0x90: case 0xA0: case 0xB0:
                            case 0xC0: case 0xD0: case 0xE0: case 0xF0:
                                gb_mmu->gb_mmap.zram[m_addr & 0x7F] = m_data;
                                return 8;
                        }
                    }

				default:
					break;
			}

    	default:
    		break;
    }
}

uint16_t mmu_read_word(gb_mmu_t *gb_mmu, uint16_t m_addr)
{
    return (mmu_read_byte(gb_mmu, m_addr) | (mmu_read_byte(gb_mmu, m_addr + 1) << 8));
}

uint8_t mmu_write_word(gb_mmu_t *gb_mmu, uint16_t m_addr, uint16_t m_data)
{
    return (uint8_t) mmu_write_byte(gb_mmu, m_addr, m_data & 0xFF) & mmu_write_byte(gb_mmu, m_addr + 1, m_data >> 8);
}

void m_load_bootrom(gb_mmu_t *gb_mmu, unsigned char *m_bootrom)
{
	memcpy((void*)gb_mmu->gb_bootrom, (const void*)m_bootrom, GB_BOOTROM_SZ);

#ifdef OPCODE_DEBUG
	printf("BootROM Dump:\n");
	for (size_t i = 0; i < GB_BOOTROM_SZ; i++)
	{
		printf("0x%x ", gb_mmu->gb_bootrom[i]);
	}
	printf("\n");
#endif
}

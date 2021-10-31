#ifndef MMU_H
#define MMU_H

#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>

// GameBoy's Bootrom Size is 256 bytes
#define GB_BOOTROM_SIZE 256
#define GB_ADDRSPC_SIZE (2^16)

typedef struct gb_mmu
{
	// 256-byte Reserved Frame for Bootrom
	uint8_t gb_bootrom[GB_BOOTROM_SIZE];

	struct
	{
		union
		{
			/*
				Maximum amount of GameBoy's address space comes determined
				by the fact that the GameBoy's Program Counter Register
				is 16-bit only (Which means 2^16 possible memory locations).

				It ranges from $0000 -> $FFFF + 1

				[1] http://gameboy.mongenel.com/dmg/asmmemmap.html

				$0000-$00FF	Restart and Interrupt Vectors
				$0100-$014F	Cartridge Header Area
				$0150-$3FFF	Cartridge ROM - Bank 0 (fixed)
				$4000-$7FFF	Cartridge ROM - Switchable Banks 1-xx
				$8000-$97FF	Character RAM
				$9800-$9BFF	BG Map Data 1
				$9C00-$9FFF	BG Map Data 2
				$A000-$BFFF	Cartridge RAM (If Available)
				$C000-$CFFF	Internal RAM - Bank 0 (fixed)
				$D000-$DFFF	Internal RAM - Bank 1-7 (switchable - CGB only)
				$E000-$FDFF	Echo RAM - Reserved, Do Not Use
				$FE00-$FE9F	OAM - Object Attribute Memory
				$FEA0-$FEFF	Unusable Memory
				$FF00-$FF7F	Hardware I/O Registers
				$FF80-$FFFE	Zero Page - 127 bytes
				$FFFF		Interrupt Enable Flag
			*/
			uint8_t gb_address_space[2^16];

/*
	Restart IVT and Cartridge Header are inside 0x4000 cart region
*/
// Restart and Interrupt Vectors (0x0 - 0x100)
#define restart_ivt 0x100

// ROM Cartridge Header (0x100 - 0x150)
#define cart_hdr 0x50

			struct
			{
				// 2 Cartridge ROM Banks (Bank 0 Fixed, 1 Switchable)
				uint8_t cart[0x4000];
				uint8_t cart_sw[0x4000];

				// Character RAM
				uint8_t cram[0x1800];

				// Background Map Data 1
				uint8_t bgmap1[0x400];

				// Background Map Data 2
				uint8_t bgmap2[0x400];

				// ROM Cartridge RAM (If Exists)
				uint8_t cart_ram[0x2000];

				// Bank 0 - Internal RAM
				uint8_t int_ram[0x1000];

				// Switchable Bank 1-7 - Internal RAM (CGB Only)
				uint8_t int_ram_sw[0x1000];

				// Echo RAM - Reserved
				uint8_t echo_ram[0x1E00];

				// Object Attribute Memory
				uint8_t oam[0xA0];

				// Unusable Memory
				uint8_t unusable[0x60];

				// Hardware I/O Registers
				uint8_t hw_io_reg[0x80];

				// Zero Page - 127 bytes
				uint8_t zero_page[0x80 - 1];

				uint8_t intenable[0x1];
			} gb_mmap;
		};
	};
	
	uint8_t *gb_bootrom_end;
} gb_mmu_t;

gb_mmu_t *mmu_init();
void mmu_halt(gb_mmu_t *gb_mmu);
uint8_t mmu_read_addr8(gb_mmu_t *gb_mmu, uint16_t m_addr);
void mmu_write_addr8(gb_mmu_t *gb_mmu, uint16_t m_addr, uint8_t m_data);
uint16_t mmu_read_addr16(gb_mmu_t *gb_mmu, uint16_t m_addr);
void mmu_write_addr16(gb_mmu_t *gb_mmu, uint16_t m_addr, uint16_t m_data);
void m_load_bootrom(gb_mmu_t *gb_mmu, unsigned char *m_bootrom);

#endif
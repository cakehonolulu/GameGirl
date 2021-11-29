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
	uint8_t m_in_bootrom;

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

			struct
			{
				// #1 Cartridge ROM Bank (Fixed)
				union {
					struct {
						// Restart and Interrupt Vectors (0x0 - 0x100)
						uint8_t restart_ivt[0x100];
						// ROM Cartridge Header (0x100 - 0x150)
						uint8_t cart_hdr[0x50];
						// Cart Size minus IVT and Header
						uint8_t cart0[0x3EB0];
					};

					// Cart containing ivt, hdr and cart0
					uint8_t cart[0x4000];
				};

				// #2 Cartridge ROM Bank (Switchable)
				uint8_t cart_sw[0x4000];

				union {
					struct {
						// Character RAM
						uint8_t cram[0x1800];
						// Background Map Data 1
						uint8_t bgmap1[0x400];
						// Background Map Data 2
						uint8_t bgmap2[0x400];
					};

					// VRAM Containing cram, bgmap[1,2]
					uint8_t vram[0x2000];
				};

				// ROM Cartridge RAM (If Exists)
				uint8_t cart_ram[0x2000];

				union {
					struct {
						// Bank 0 - Internal RAM
						uint8_t int_ram[0x1000];
						// Switchable Bank 1-7 - Internal RAM (CGB Only)
						uint8_t int_ram_sw[0x1000];
					};

					// WRAM
					uint8_t wram[0x2000];
				};

				// Echo RAM - Reserved
				uint8_t echo_ram[0x1E00];

				// Object Attribute Memory
				uint8_t oam[0xA0];

				// Unusable Memory
				uint8_t unusable[0x60];

				union {
					struct {
						// IO Registers Mapping
						uint8_t io[0x40];
						// PPU Mapping
						uint8_t ppu[0x40];	
					};

					// Hardware I/O Registers
					uint8_t hw_io_reg[0x80];
				};

				union {
					struct {
						// Zero Page - 127 bytes
						uint8_t zero_page[0x80 - 1];
						// Interrupt Enable
						uint8_t intenable[0x1];
					};

					// Zero-Page RAM
					uint8_t zram[0x80];
				};

			} gb_mmap;
		};
	};
} gb_mmu_t;

extern gb_mmu_t *mmu;

gb_mmu_t *mmu_init();
void mmu_halt();

void m_init_address_space();

// DMA-Like R/W, no MMU use at all, better use MMU-Safe alternatives
uint8_t mmu_read_addr8(uint16_t m_addr);
void mmu_write_addr8(uint16_t m_addr, uint8_t m_data);
uint16_t mmu_read_addr16(uint16_t m_addr);
void mmu_write_addr16(uint16_t m_addr, uint16_t m_data);

// MMU-Safe alternatives
uint8_t mmu_read_byte(uint16_t m_addr);
uint8_t mmu_write_byte(uint16_t m_addr, uint8_t m_data);
uint16_t mmu_read_word(uint16_t m_addr);
uint8_t mmu_write_word(uint16_t m_addr, uint16_t m_data);

void m_load_bootrom(unsigned char *m_bootrom);

#endif
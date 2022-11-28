#ifndef GAMEGIRL_H
#define GAMEGIRL_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#if defined(PREC23)
#include <stdbool.h>
#endif
#include <bit/bits.h>
#include <SDL2/SDL.h>

#define GB_INITIAL_PC 0x0000

#define GB_BOOTROM_SZ 0x100

struct m_gb_flags {
#if !defined(PREC23)
	unsigned _BitInt(1) zero;
	unsigned _BitInt(1) ngtv;
	unsigned _BitInt(1) half;
	unsigned _BitInt(1) crry;
#else
	uint8_t zero;
	uint8_t ngtv;
	uint8_t half;
	uint8_t crry;
#endif
};

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
			uint8_t gb_address_space[1 << 16];

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
						uint8_t intenable;
					};

					// Zero-Page RAM
					uint8_t zram[0x80];
				};

			} gb_mmap;
		};
	};
} gb_mmu_t;

typedef struct gb_registers {
	struct {
		union {
			struct {
				uint8_t f;
				uint8_t a;
			};
			uint16_t af;
		};
	};
	
	struct {
		union {
			struct {
				uint8_t c;
				uint8_t b;
			};
			uint16_t bc;
		};
	};
	
	struct {
		union {
			struct {
				uint8_t e;
				uint8_t d;
			};
			uint16_t de;
		};
	};
	
	struct {
		union {
			struct {
				uint8_t l;
				uint8_t h;
			};
			uint16_t hl;


			
		};
	};
	
	struct {

		uint16_t pc;
		uint16_t sp;

	};

	struct m_gb_flags m_flags;
} gb_registers_t;


enum {
	M_GPU_HBLANK = 0,
	M_GPU_VBLANK = 1,
	M_GPU_OAM = 2,
	M_GPU_VRAM = 3
};

#define M_DMG01_ROWS 144
#define M_DMG01_COLS 160

// FF40 LCDC - LCD Control
#define GPU_CONTROL_BGENABLE (1 << 0)
#define GPU_CONTROL_SPRITEENABLE (1 << 1)
#define GPU_CONTROL_SPRITEVDOUBLE (1 << 2)
#define GPU_CONTROL_TILEMAP (1 << 3)
#define GPU_CONTROL_TILESET (1 << 4)
#define GPU_CONTROL_WINDOWENABLE (1 << 5)
#define GPU_CONTROL_WINDOWTILEMAP (1 << 6)
#define GPU_CONTROL_DISPLAYENABLE (1 << 7)

// Declare a structure with the PPU's foundations
// DMG-01's Screen's Resolution equals to 160 x 144 (px)
typedef struct ppu_t
{
	uint8_t m_lcdc;					// Current PPU Mode [$FF40]
	uint8_t m_stat;					// PPU Tileset Control [$FF41]
	uint8_t m_verticalscroll;		// Y Coordinate (Vertical, 144px-wide) [$FF42]
	uint8_t m_horitzontalscroll;	// X coordinate (Horitzontal, 160px-wide) [$FF43]
	uint8_t m_scanline;				// Current scanline (DMG-01 imitates a CRT monitor) [$FF44]
	uint8_t m_palette;				// Color Palette [$FF47]

	uint32_t colors[4];
	uint8_t palette[4];

	uint8_t tileset[0x180][8][8];

    uint32_t framebuffer[160 * 144];

	uint64_t m_ticks;				// Current PPU Ticks
} m_ppu_t;


#define INT_VBLANK	(1 << 0)
#define INT_LCD		(1 << 1)
#define INT_TIMER	(1 << 2)
#define INT_SERIAL	(1 << 3)
#define INT_JOYPAD	(1 << 4)

typedef struct m_interrupt
{
#if !defined(PREC23)
	unsigned _BitInt(1) m_master;
#else
	uint8_t m_master;
#endif
	uint8_t m_enabled;
	uint8_t m_flags;
} m_interrupts;

typedef struct m_sharp_lr35902 {

	gb_registers_t *m_registers;

	m_interrupts *interrupts;

	uint64_t m_cpu_ticks;

	uint8_t prev_pc;

	uint8_t m_opcode;
	uint8_t m_boperand;
	uint16_t m_woperand;

} m_dmg_cpu;

typedef struct m_gb_state {

	gb_mmu_t *m_memory;

	m_dmg_cpu *m_cpu;

	m_ppu_t *ppu;

	SDL_Window   *m_window;
	SDL_Renderer *m_renderer;
	SDL_Texture *m_texture;

	// Declare an SDL2 Event Handler
	SDL_Event m_event;

	bool m_speedhack;
} m_dmg_t;

#define IME (m_dmg->m_cpu->interrupts->m_master)
#define IE (m_dmg->m_cpu->interrupts->m_enabled)
#define IF (m_dmg->m_cpu->interrupts->m_flags)

// Register defines with easier naming
#define A_REG (m_dmg->m_cpu->m_registers->a)
#define F (m_dmg->m_cpu->m_registers->f)
#define AF (m_dmg->m_cpu->m_registers->af)

#define B_REG (m_dmg->m_cpu->m_registers->b)
#define C (m_dmg->m_cpu->m_registers->c)
#define BC (m_dmg->m_cpu->m_registers->bc)

#define D (m_dmg->m_cpu->m_registers->d)
#define E (m_dmg->m_cpu->m_registers->e)
#define DE (m_dmg->m_cpu->m_registers->de)

#define H (m_dmg->m_cpu->m_registers->h)
#define L (m_dmg->m_cpu->m_registers->l)
#define HL (m_dmg->m_cpu->m_registers->hl)

// Stack-pointer register
#define SP (m_dmg->m_cpu->m_registers->sp)

// Program counter register
#define PC (m_dmg->m_cpu->m_registers->pc)

// Flags register (Most-Significant Nibble of a Byte is only used)
#define FLAGS (m_dmg->m_cpu->m_registers->m_flags)

typedef enum {
	ZERO = 4,
	NGTV = 3,
	HALF = 2,
	CRRY = 1	
} m_cpu_flags;

#include <flags.h>

#define FLAG_SET(flag) flag_set(m_dmg, flag)
#define FLAG_UNSET(flag) flag_unset(m_dmg, flag)
#define FLAG_CHECK(flag) flag_check(m_dmg, flag)

#endif

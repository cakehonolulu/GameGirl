#ifndef GAMEGIRL_H
#define GAMEGIRL_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <mmu.h>

#define GB_INITIAL_PC 0x0000

#define GB_BOOTROM_SZ 0x100

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
	
	uint16_t sp;
	uint16_t pc;

	uint8_t flags;

	bool isUnimplemented;
} gb_registers_t;

// Declare the MMU
extern gb_mmu_t *mmu;
// Declare the Registers
extern gb_registers_t m_regs;

#define ZERO 0b0111
#define NGTV 0b0110
#define HALF 0b0101
#define CRRY 0b0100

#define A (m_regs.a)
#define F (m_regs.f)
#define AF (m_regs.af)

#define B (m_regs.b)
#define C (m_regs.c)
#define BC (m_regs.bc)

#define D (m_regs.d)
#define E (m_regs.e)
#define DE (m_regs.de)

#define H (m_regs.h)
#define L (m_regs.l)
#define HL (m_regs.hl)

#define SP (m_regs.sp)
#define PC (m_regs.pc)
#define FLAGS (m_regs.flags)

#define FLAG_SET(n) ((FLAGS) |= (1 << n))
#define FLAG_UNSET(n) ((FLAGS) &= ~(1 << (n)))

#endif

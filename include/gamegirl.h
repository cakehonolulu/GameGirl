#ifndef GAMEGIRL_H
#define GAMEGIRL_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <mmu.h>
#include <bit/bits.h>

#define GB_INITIAL_PC 0x0000

#define GB_BOOTROM_SZ 0x100

struct m_gb_flags {
	unsigned _BitInt(1) zero;
	unsigned _BitInt(1) ngtv;
	unsigned _BitInt(1) half;
	unsigned _BitInt(1) crry;
};

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

	struct m_gb_flags m_flags;

	bool isUnimplemented;
} gb_registers_t;

// Declare the MMU
extern gb_mmu_t *mmu;
// Declare the Registers
extern gb_registers_t m_regs;


// Register defines with easier naming
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

// Stack-pointer register
#define SP (m_regs.sp)

// Program counter register
#define PC (m_regs.pc)

// Flags register (Most-Significant Nibble of a Byte is only used)
#define FLAGS (m_regs.flags)

// Flag register flags
#define ZERO 4 // 4th bit
#define NGTV 3 // 3rd bit
#define HALF 2 // 2nd bit
#define CRRY 1 // 1st bit

// Flag set-unset-check macros
#define FLAG_SET(flag) flag_set(flag)
#define FLAG_UNSET(flag) flag_unset(flag)
#define FLAG_CHECK(flag) flag_check(flag)

#endif

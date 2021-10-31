#ifndef GAMEGIRL_H
#define GAMEGIRL_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "mmu.h"

#define GB_INITIAL_PC 0x0000

#define Z 0b0111
#define N 0b0110
#define H 0b0101
#define C 0b0100

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

#define FLAG_SET(x, n) ((x) |= (1 << n))
#define FLAG_UNSET(x, n) ((x) &= ~(1 << (n)))
#endif
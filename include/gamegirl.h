#ifndef GAMEGIRL_H
#define GAMEGIRL_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#define GB_INITIAL_PC 0x0000

#define FLAGS_ZERO 0b10000000
#define FLAGS_SUBS 0b01000000
#define FLAGS_HALF 0b00100000
#define FLAGS_CRRY 0b00010000

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

#define FLAGS (m_regs->flags)
#define FLAG_SET(n) (FLAGS ^= (1 << n))
#define FLAG_UNSET(n) (FLAGS &= ~(1 << n))
#endif
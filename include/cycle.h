#ifndef CYCLE_H
#define CYCLE_H

#include "gamegirl.h"
#include "mmu.h"

void m_init_registers(gb_registers_t m_regs);
uint8_t m_fetch(gb_registers_t m_regs);
void m_exec(gb_registers_t m_regs);

#endif
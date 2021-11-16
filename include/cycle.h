#ifndef CYCLE_H
#define CYCLE_H

#include <gamegirl.h>
#include <mmu.h>

void m_init_registers();
uint8_t m_fetch();
void m_exec();
void m_printregs();

bool m_is_bit_set(uint8_t m_register, size_t m_bit);

#endif

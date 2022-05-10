#ifndef CYCLE_H
#define CYCLE_H

#include <gamegirl.h>
#include <mmu.h>

void m_init_registers(m_dmg_t *m_dmg);
uint8_t m_fetch(m_dmg_t *m_dmg);
size_t m_exec(m_dmg_t *m_dmg);
void m_printregs(m_dmg_t *m_dmg);

bool m_is_bit_set(uint8_t m_register, size_t m_bit);

#endif

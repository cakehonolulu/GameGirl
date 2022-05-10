#include <stdint.h>
#include <stddef.h>
#include <gamegirl.h>

void m_ppu_step(m_dmg_t *m_dmg, size_t m_cycles);
void m_ppu_update_palette(m_dmg_t *m_dmg, uint8_t m_data);
void m_ppu_update_tile(m_dmg_t *m_dmg, uint16_t m_addr);
void m_ppu_init(m_dmg_t *m_dmg);

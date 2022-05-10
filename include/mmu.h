#ifndef MMU_H
#define MMU_H

#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#ifdef PREC23
#include <stdbool.h>
#endif
#include <string.h>

#include <gamegirl.h>

void mmu_init(m_dmg_t *m_dmg);
void mmu_halt(m_dmg_t *m_dmg);

void m_init_address_space(m_dmg_t *m_dmg);

// DMA-Like R/W, no MMU use at all, better use MMU-Safe alternatives
uint8_t mmu_read_addr8(m_dmg_t *m_dmg, uint16_t m_addr);
void mmu_write_addr8(m_dmg_t *m_dmg, uint16_t m_addr, uint8_t m_data);
uint16_t mmu_read_addr16(m_dmg_t *m_dmg, uint16_t m_addr);
void mmu_write_addr16(m_dmg_t *m_dmg, uint16_t m_addr, uint16_t m_data);

// MMU-Safe alternatives
uint8_t mmu_read_byte(m_dmg_t *m_dmg, uint16_t m_addr);
uint8_t mmu_write_byte(m_dmg_t *m_dmg, uint16_t m_addr, uint8_t m_data);
uint16_t mmu_read_word(m_dmg_t *m_dmg, uint16_t m_addr);
uint8_t mmu_write_word(m_dmg_t *m_dmg, uint16_t m_addr, uint16_t m_data);

void m_load_bootrom(m_dmg_t *m_dmg, unsigned char *m_bootrom);
void m_load_rom(m_dmg_t *m_dmg, unsigned char *m_rom, size_t m_rom_sz);

/* Macro declarations */
#define READB(addr) (mmu_read_byte(m_dmg, addr))
#define WRITEB(addr, val) (mmu_write_byte(m_dmg, addr, val))
#define READW(addr) (mmu_read_word(m_dmg, addr))
#define WRITEW(addr, val) (mmu_write_word(m_dmg, addr, val))
#endif

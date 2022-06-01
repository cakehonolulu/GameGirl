#include <stdint.h>
#include <gamegirl.h>

/* Function declarations */
uint16_t stack_pushw(m_dmg_t *m_dmg, uint16_t m_value);
uint16_t stack_popw(m_dmg_t *m_dmg);

/* Macro declarations */
#define PUSHW(val) (stack_pushw(m_dmg, val))
#define POPW() (stack_popw(m_dmg))

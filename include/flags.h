#include <stdint.h>
#include <gamegirl.h>

void flag_set(m_dmg_t *m_dmg, m_cpu_flags m_flag);
void flag_unset(m_dmg_t *m_dmg, m_cpu_flags m_flag);
bool flag_check(m_dmg_t *m_dmg, m_cpu_flags m_flag);

uint8_t m_flags_get(m_dmg_t *m_dmg);
uint16_t m_flags_combine_af(m_dmg_t *m_dmg);
void m_flags_reg_set(m_dmg_t *m_dmg, uint8_t m_flags);
void m_af_reg_set(m_dmg_t *m_dmg, uint16_t m_af);

#define FLAG_SET(flag) flag_set(m_dmg, flag)
#define FLAG_UNSET(flag) flag_unset(m_dmg, flag)
#define FLAG_CHECK(flag) flag_check(m_dmg, flag)

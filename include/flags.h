#include <stdint.h>
#include <gamegirl.h>

void flag_set(m_dmg_t *m_dmg, m_cpu_flags m_flag);
void flag_unset(m_dmg_t *m_dmg, m_cpu_flags m_flag);
bool flag_check(m_dmg_t *m_dmg, m_cpu_flags m_flag);

#define FLAG_SET(flag) flag_set(m_dmg, flag)
#define FLAG_UNSET(flag) flag_unset(m_dmg, flag)
#define FLAG_CHECK(flag) flag_check(m_dmg, flag)

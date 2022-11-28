#include <stdint.h>
#include <gamegirl.h>

void flag_set(m_dmg_t *m_dmg, m_cpu_flags m_flag);
void flag_unset(m_dmg_t *m_dmg, m_cpu_flags m_flag);
bool flag_check(m_dmg_t *m_dmg, m_cpu_flags m_flag);

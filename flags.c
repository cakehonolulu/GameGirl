#include <gamegirl.h>

// Flag set-unset-check macros
void flag_set(m_dmg_t *m_dmg, m_cpu_flags m_flag)
{
	switch (m_flag)
	{
		case ZERO:
			m_dmg->m_cpu->m_registers->m_flags.zero = 1;
			break;

		case NGTV:
			m_dmg->m_cpu->m_registers->m_flags.ngtv = 1;
			break;

		case HALF:
			m_dmg->m_cpu->m_registers->m_flags.half = 1;
			break;

		case CRRY:
			m_dmg->m_cpu->m_registers->m_flags.crry = 1;
			break;

		default:
			__builtin_unreachable();
	}
}

void flag_unset(m_dmg_t *m_dmg, m_cpu_flags m_flag)
{
	switch (m_flag)
	{
		case ZERO:
			m_dmg->m_cpu->m_registers->m_flags.zero = 0;
			break;

		case NGTV:
			m_dmg->m_cpu->m_registers->m_flags.ngtv = 0;
			break;

		case HALF:
			m_dmg->m_cpu->m_registers->m_flags.half = 0;
			break;

		case CRRY:
			m_dmg->m_cpu->m_registers->m_flags.crry = 0;
			break;

		default:
			__builtin_unreachable();
	}
}

bool flag_check(m_dmg_t *m_dmg, m_cpu_flags m_flag)
{
	bool m_flag_status = false;

	switch (m_flag)
	{
		case ZERO:
			m_flag_status = m_dmg->m_cpu->m_registers->m_flags.zero;
			break;

		case NGTV:
			m_flag_status = m_dmg->m_cpu->m_registers->m_flags.ngtv;
			break;

		case HALF:
			m_flag_status = m_dmg->m_cpu->m_registers->m_flags.half;
			break;

		case CRRY:
			m_flag_status = m_dmg->m_cpu->m_registers->m_flags.crry;
			break;

		default:
			__builtin_unreachable();
	}

	return m_flag_status;
}

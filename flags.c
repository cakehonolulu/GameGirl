#include <gamegirl.h>

// Flag set-unset-check macros
void flag_set(m_dmg_t *m_dmg, uint8_t m_flag)
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
			break;
	}
}

void flag_unset(m_dmg_t *m_dmg, uint8_t m_flag)
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
			break;
	}
}

uint8_t flag_check(m_dmg_t *m_dmg, uint8_t m_flag)
{
	switch (m_flag)
	{
		case ZERO:
			return m_dmg->m_cpu->m_registers->m_flags.zero;

		case NGTV:
			return m_dmg->m_cpu->m_registers->m_flags.ngtv;

		case HALF:
			return m_dmg->m_cpu->m_registers->m_flags.half;

		case CRRY:
			return m_dmg->m_cpu->m_registers->m_flags.crry;

		default:
			break;
	}

	// Error?
	return 9;
}

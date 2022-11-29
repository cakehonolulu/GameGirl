#include <flags.h>

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

uint8_t m_flags_get(m_dmg_t *m_dmg)
{
	uint8_t m_flags = 0;

#if defined(PREC23) || !defined(USE_GCC)
	if (FLAG_CHECK(ZERO))
#else
	if (m_is_bit_set(FLAGS, ZERO))
#endif
	{
		m_flags |= 1 << 7;
	}

#if defined(PREC23) || !defined(USE_GCC)
	if (FLAG_CHECK(NGTV))
#else
	if (m_is_bit_set(FLAGS, NGTV))
#endif
	{
		m_flags |= 1 << 6;
	}

#if defined(PREC23) || !defined(USE_GCC)
	if (FLAG_CHECK(HALF))
#else
	if (m_is_bit_set(FLAGS, HALF))
#endif
	{
		m_flags |= 1 << 5;
	}

#if defined(PREC23) || !defined(USE_GCC)
	if (FLAG_CHECK(CRRY))
#else
	if (m_is_bit_set(FLAGS, CRRY))
#endif
	{
		m_flags |= 1 << 4;
	}

	return m_flags;
}

uint16_t m_flags_combine_af(m_dmg_t *m_dmg)
{	
	return ((A_REG << 8) | m_flags_get(m_dmg));
}

void m_flags_reg_set(m_dmg_t *m_dmg, uint8_t m_flags)
{
	m_dmg->m_cpu->m_registers->m_flags.zero = ((m_flags >> ZERO) & 1);
	m_dmg->m_cpu->m_registers->m_flags.ngtv = ((m_flags >> NGTV) & 1);
	m_dmg->m_cpu->m_registers->m_flags.half = ((m_flags >> HALF) & 1);
	m_dmg->m_cpu->m_registers->m_flags.crry = ((m_flags >> CRRY) & 1);
}

void m_af_reg_set(m_dmg_t *m_dmg, uint16_t m_af)
{
	m_flags_reg_set(m_dmg, ((uint8_t) m_af));

	A_REG = ((uint8_t) ((m_af & 0xFF00) >> 8));
}

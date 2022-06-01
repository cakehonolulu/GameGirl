#include <interrupts.h>
#include <stdio.h>

void m_interrupt_check(m_dmg_t *m_dmg)
{
	if (m_dmg->m_cpu->interrupts->m_master && m_dmg->m_cpu->interrupts->m_enabled && m_dmg->m_cpu->interrupts->m_flags)
	{
		uint8_t m_int = m_dmg->m_cpu->interrupts->m_enabled & m_dmg->m_cpu->interrupts->m_flags;
		
		if (m_int & INT_VBLANK)
		{
			m_dmg->m_cpu->interrupts->m_enabled &= ~INT_VBLANK;
			printf("VBlank!\n");
		}
		
		if (m_int & INT_LCD)
		{
			m_dmg->m_cpu->interrupts->m_enabled &= ~INT_LCD;
			printf("LCD!\n");
		}
		
		if (m_int & INT_TIMER)
		{
			m_dmg->m_cpu->interrupts->m_enabled &= ~INT_TIMER;
			printf("TIMER!\n");
		}
		
		if (m_int & INT_SERIAL)
		{
			m_dmg->m_cpu->interrupts->m_enabled &= ~INT_SERIAL;
			printf("SERIAL!\n");
		}
		
		if (m_int & INT_JOYPAD)
		{
			m_dmg->m_cpu->interrupts->m_enabled &= ~INT_JOYPAD;
			printf("JOYPAD!\n");
		}
	}
}

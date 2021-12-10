#include <interrupts.h>
#include <stdio.h>

m_interrupts interrupts;

void m_interrupt_check()
{
	if (interrupts.m_master && interrupts.m_enabled && interrupts.m_flags)
	{
		uint8_t m_int = interrupts.m_enabled & interrupts.m_flags;
		
		if (m_int & INT_VBLANK)
		{
			interrupts.m_enabled &= ~INT_VBLANK;
			printf("VBlank!\n");
		}
		
		if (m_int & INT_LCD)
		{
			interrupts.m_enabled &= ~INT_LCD;
			printf("LCD!\n");
		}
		
		if (m_int & INT_TIMER)
		{
			interrupts.m_enabled &= ~INT_TIMER;
			printf("TIMER!\n");
		}
		
		if (m_int & INT_SERIAL)
		{
			interrupts.m_enabled &= ~INT_SERIAL;
			printf("SERIAL!\n");
		}
		
		if (m_int & INT_JOYPAD)
		{
			interrupts.m_enabled &= ~INT_JOYPAD;
			printf("JOYPAD!\n");
		}
	}
}
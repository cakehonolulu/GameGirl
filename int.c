#include <int.h>

m_interrupts ints;

void m_int_check()
{
	if(ints.m_master && ints.m_enabled && ints.m_flags)
	{
		uint8_t m_int = ints.m_enabled & ints.m_flags;
		
		if (m_int & INT_VBLANK)
		{
			ints.m_enabled &= ~INT_VBLANK;
			printf("VBlank!\n");
		}
		
		if (m_int & INT_LCD)
		{
			ints.m_enabled &= ~INT_LCD;
			printf("LCD!\n");
		}
		
		if (m_int & INT_TIMER)
		{
			ints.m_enabled &= ~INT_TIMER;
			printf("TIMER!\n");
		}
		
		if (m_int & INT_SERIAL)
		{
			ints.m_enabled &= ~INT_SERIAL;
			printf("SERIAL!\n");
		}
		
		if (m_int & INT_JOYPAD)
		{
			ints.m_enabled &= ~INT_JOYPAD;
			printf("JOYPAD!\n");
		}
	}
}
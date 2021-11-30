#include <alu.h>

/*
	alu.c

	This file contains the source code that implements basic
	arithmetic-logic-unit tasks (Register increment, decrement...)
	to enhance code readability and simplify code.
*/

// Register increment (Lone-pair-register exclusive)
uint8_t increment(uint8_t m_register)
{
	/*
		Check if we need to enable half-carry bit
		Mask the lower nibble of the register and
		compare it with 0b00001111
	*/
	if ((m_register & 0b00001111) == 0b00001111)
	{
		// Set the Half-Carry bit
		FLAG_SET(HALF);
	}
	else
	{
		// Clear the Half-Carry bit
		FLAG_UNSET(HALF);
	}

	// Increment the register value
	m_register++;

	// Check if register value is not zero
	if (m_register != 0)
	{
		// Unset the Zero (Result) flag
		FLAG_UNSET(ZERO);
	}
	else
	{
		// Set the Zero (Result) flag
		FLAG_SET(ZERO);
	}

	// Finally, clear the negative flag as we're dealing with increments
	FLAG_UNSET(NGTV);

	return m_register;
}

// Register decrement (Lone-pair-register exclusive)
uint8_t decrement(uint8_t m_register)
{
	// Check if we need to enable half-carry bit
	if (m_register & 0b00001111)
	{
		// Clear the Half-Carry bit
		FLAG_UNSET(HALF);
	}
	else
	{
		// Set the Half-Carry bit
		FLAG_SET(HALF);
	}
	
	// Decrement the register value
	m_register--;
	
	// Check if register value is not zero
	if (m_register != 0)
	{
		FLAG_UNSET(ZERO);
	}
	else
	{
		FLAG_SET(ZERO);
	}

	// Finally, set the negative bit in flags register as we just decremented a register
	FLAG_SET(NGTV);
	
	return m_register;
}

uint8_t addition(uint8_t *m_register, uint8_t m_value)
{
	uint32_t m_result = *m_register + m_value;

	if (m_result & 0b11110000)
	{
		FLAG_SET(CRRY);
	}
	else
	{
		FLAG_UNSET(CRRY);
	}

	*m_register = (uint8_t) (m_result & 0xFF);

	if (*m_register)
	{
		FLAG_UNSET(ZERO);
	}
	else
	{
		FLAG_SET(ZERO);
	}

	if (((*m_register & 0x0F) + (m_value & 0x0F)) > 0x0F)
	{
		FLAG_SET(HALF);
	}
	else
	{
		FLAG_UNSET(HALF);
	}

	FLAG_UNSET(NGTV);

	return m_register;
}
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
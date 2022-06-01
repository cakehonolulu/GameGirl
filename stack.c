#include <stack.h>
#include <mmu.h>

// The following function pushes a word-sized (2 Byte) value to the stack
uint16_t stack_pushw(m_dmg_t *m_dmg, uint16_t m_value)
{
	// Decrement the stack pointer
	SP -= 2;

	// "Push" (Write to addr.) the value to the stack
	WRITEW(SP, m_value);

	// Return current stack pointer value
	return SP;
}

// The following function pops a word-sized (2 Byte) value from the stack
uint16_t stack_popw(m_dmg_t *m_dmg)
{
	// Read the word-sized value from the current Stack Pointer
	uint16_t m_value = READW(SP);
	
	// Increment the Stack Pointer value by 2
	SP += 2;

	// Return the "popped" value
	return m_value;
}

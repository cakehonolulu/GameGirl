#include <stack.h>

// The following function pushes a word-sized (2 Byte) value to the stack
uint16_t stack_pushw(uint16_t m_value)
{
	// Decrement the stack pointer
	SP -= 2;

	// "Push" (Write to addr.) the value to the stack
	mmu_write_word(SP, m_value);

	// Return current stack pointer value
	return SP;
}
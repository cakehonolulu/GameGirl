#include <stdint.h>
#include <gamegirl.h>

/* Function declarations */
uint16_t stack_pushw(uint16_t m_value);

/* Macro declarations */
#define PUSHW(val) (stack_pushw(val))
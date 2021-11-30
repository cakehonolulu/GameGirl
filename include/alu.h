#include <gamegirl.h>

// ALU Log-level types
enum alu_loglevels
{
	ALU_NORMAL = 0,
	ALU_WARNING = 1,
	ALU_ERROR = 2
};

// Arithmetic-Logic-Unit Special Messaging Macros
#define alu_message(loglevel, msg, ...) do { if (loglevel == ALU_NORMAL) { printf("[ALU] %s\n", msg); } else if (loglevel == ALU_ERROR) { printf("[ALU] \033[0;31m%s\033[0;0m\n", msg); } } while (0)

// ALU Normal Message
#define alu_printf(msg) alu_message(ALU_NORMAL, msg)

// ALU Error Message
#define alu_error(msg) alu_message(ALU_ERROR, msg)

// Increment a 8-bit register
uint8_t increment(uint8_t m_register);

// Decrement a 8-bit register
uint8_t decrement(uint8_t m_register);

// Add m_value to an 8-bit register
uint8_t addition(uint8_t *m_register, uint8_t m_value);

// Macros for easier working
#define INC(reg) (reg = increment(reg))
#define DEC(reg) (reg = decrement(reg))
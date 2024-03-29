#include <stdint.h>

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
uint8_t increment(m_dmg_t *m_dmg, uint8_t m_register);

// Decrement a 8-bit register
uint8_t decrement(m_dmg_t *m_dmg, uint8_t m_register);

// Add m_value to an 8-bit register
uint8_t addition(m_dmg_t *m_dmg, uint8_t *m_register, uint8_t m_value);

// Add m_value to a 16-bit register
uint16_t word_addition(m_dmg_t *m_dmg, uint16_t *m_register, uint16_t m_value);

// OR an 8-bit register contents
uint8_t or(m_dmg_t *m_dmg, uint8_t m_register);

// Set 'nth bit to 1 on a determinate variable
uint8_t set_bit(uint8_t m_var, uint8_t m_bit);

// Macros for easier working
#define INC(reg) (reg = increment(m_dmg, reg))
#define DEC(reg) (reg = decrement(m_dmg, reg))

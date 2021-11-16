#include <gamegirl.h>

// ALU Log-level types
enum alu_loglevels
{
	NORMAL = 0,
	WARNING = 1,
	ERROR = 2
};

// Arithmetic-Logic-Unit Special Messaging Macros
#define alu_message(loglevel, msg, ...) do { if (loglevel == NORMAL) { printf("[ALU] %s\n", msg); } else if (loglevel == ERROR) { printf("[ALU] \033[0;31m%s\033[0;0m\n", msg); } } while (0)

// ALU Normal Message
#define alu_printf(msg) alu_message(NORMAL, msg)

// ALU Error Message
#define alu_error(msg) alu_message(ERROR, msg)

// Increment a 8-bit register
uint8_t increment(uint8_t m_register);

#define INC(reg) (reg = increment(reg))
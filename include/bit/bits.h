#include <stdint.h>

/*
	Intended use for byte-sized variables (uint8_t)
*/
// Sets [to], [bit] number to 1
#define BIT_SET(to, bit) ((to) |= (1 << bit))

// Unsets [to], [bit] number to 1
#define BIT_UNSET(to, bit) ((to) &= ~(1 << (bit)))
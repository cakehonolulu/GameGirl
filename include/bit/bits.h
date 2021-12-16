#include <stdint.h>

#ifdef PREC23
/*
	Intended use for byte-sized variables (uint8_t)
*/
// Sets [in]'s [bit] to 1
#define BIT_SET(in, bit) ((in) |= (1 << bit))

// Unsets [in]'s [bit]
#define BIT_UNSET(in, bit) ((in) &= ~(1 << (bit)))

// Checks [in]'s bit state
#define BIT_CHECK(in, bit) ((in & (1 << bit)))
#endif
#include <stdint.h>

uint8_t m_cgpu_mode;

uint64_t m_gpu_ticks;

extern uint64_t m_cpu_ticks;

enum {
	M_GPU_HBLANK = 0,
	M_GPU_VBLANK = 1,
	M_GPU_OAM = 2,
	M_GPU_VRAM = 3
};

#define M_DMG01_ROWS 144
#define M_DMG01_COLS 160

// Declare a structure with the PPU's foundations
// DMG-01's Screen's Resolution equals to 160 x 144 (px)
typedef struct m_gpu
{
	uint8_t m_scanline;				// Current scanline (DMG-01 imitates a CRT monitor)
	uint8_t m_lateralscroll;		// X coordinate (Horitzontal, 160px-wide)
	uint8_t m_verticalscroll;		// Y Coordinate (Vertical, 144px-wide)
};
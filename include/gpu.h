#include <stdint.h>

extern uint64_t m_cpu_ticks;

enum {
	M_GPU_HBLANK = 0,
	M_GPU_VBLANK = 1,
	M_GPU_OAM = 2,
	M_GPU_VRAM = 3
};

#define M_DMG01_ROWS 144
#define M_DMG01_COLS 160

// FF40 LCDC - LCD Control
#define GPU_CONTROL_BGENABLE (1 << 0)
#define GPU_CONTROL_SPRITEENABLE (1 << 1)
#define GPU_CONTROL_SPRITEVDOUBLE (1 << 2)
#define GPU_CONTROL_TILEMAP (1 << 3)
#define GPU_CONTROL_TILESET (1 << 4)
#define GPU_CONTROL_WINDOWENABLE (1 << 5)
#define GPU_CONTROL_WINDOWTILEMAP (1 << 6)
#define GPU_CONTROL_DISPLAYENABLE (1 << 7)

// Declare a structure with the PPU's foundations
// DMG-01's Screen's Resolution equals to 160 x 144 (px)
typedef struct gpu_t
{
	uint8_t m_lcdc;					// Current PPU Mode [$FF40]
	uint8_t m_stat;					// PPU Tileset Control [$FF41]
	uint8_t m_verticalscroll;		// Y Coordinate (Vertical, 144px-wide) [$FF42]
	uint8_t m_horitzontalscroll;	// X coordinate (Horitzontal, 160px-wide) [$FF43]
	uint8_t m_scanline;				// Current scanline (DMG-01 imitates a CRT monitor) [$FF44]
	uint8_t m_palette;				// Color Palette [$FF47]
	uint64_t m_ticks;				// Current PPU Ticks
} m_gpu_t;

extern m_gpu_t gpu;

extern uint8_t tiles[512][8][8];

struct rgb {
	unsigned char r, g, b;
} extern framebuffer[160 * 144];

extern const struct rgb palette[4];
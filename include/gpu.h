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
#include "include/gpu.h"

static uint64_t m_gpu_elapsed_ticks = 0;

m_gpu_t gpu;

void m_gpu_step()
{
	gpu.m_cgpu_mode = M_GPU_HBLANK;
	
	gpu.m_ticks += m_cpu_ticks - m_gpu_elapsed_ticks;
	
	m_gpu_elapsed_ticks = m_cpu_ticks;

	switch (gpu.m_cgpu_mode)
	{
		case M_GPU_HBLANK:
			break;

		case M_GPU_VBLANK:
			break;

		case M_GPU_OAM:
			break;

		case M_GPU_VRAM:
			break;

		default:
			break;
	}

}
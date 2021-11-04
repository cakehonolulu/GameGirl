#include "include/gpu.h"

static uint64_t m_gpu_elapsed_ticks;

m_gpu_t gpu;

void m_gpu_step()
{
	gpu.m_cgpu_mode = M_GPU_HBLANK;
	
	gpu.m_ticks += m_cpu_ticks - m_gpu_elapsed_ticks;
	
	m_gpu_elapsed_ticks = m_cpu_ticks;

	switch (gpu.m_cgpu_mode)
	{



		default:
			break;
	}

}
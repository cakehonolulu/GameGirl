#include "include/gpu.h"

static uint64_t m_gpu_elapsed_ticks;

void m_gpu_step()
{
	m_cgpu_mode = M_GPU_HBLANK;
	
	m_gpu_ticks += m_cpu_ticks - m_gpu_elapsed_ticks;
	
	m_gpu_elapsed_ticks = m_cpu_ticks;

	switch (m_cgpu_mode)
	{



		default:
			break;
	}

}
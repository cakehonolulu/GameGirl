#include "include/gpu.h"
#include "include/int.h"

static uint64_t m_gpu_elapsed_ticks = 0;

m_gpu_t gpu;

void m_gpu_step()
{
	gpu.m_ticks += m_cpu_ticks - m_gpu_elapsed_ticks;
	
	m_gpu_elapsed_ticks = m_cpu_ticks;

	switch (gpu.m_stat)
	{
		case M_GPU_HBLANK:
			if (gpu.m_ticks >= 204)
			{
				gpu.m_scanline++;

				if (gpu.m_scanline == 143)
				{
					/*if (ints.m_enabled & INT_VBLANK)
					{
						ints.m_flags |= INT_VBLANK;*/
						gpu.m_stat = M_GPU_VBLANK;
					/*} else {
						gpu.m_cgpu_mode = M_GPU_OAM;
						gpu.m_ticks -= 204;
					}*/
				}
			}
			break;

		case M_GPU_VBLANK:
			if (gpu.m_ticks >= 456)
			{
				gpu.m_scanline++;		

				if (gpu.m_scanline > 153)
				{
					gpu.m_stat = M_GPU_OAM;
					gpu.m_scanline = 0;
				}

				gpu.m_ticks -= 456;
			}
			break;

		case M_GPU_OAM:
			if (gpu.m_ticks >= 80)
			{
				gpu.m_stat = M_GPU_VRAM;
				
				gpu.m_ticks -= 80;
			}
			break;

		case M_GPU_VRAM:
			if (gpu.m_ticks >= 172)
			{
				gpu.m_stat = M_GPU_HBLANK;

				m_render_sc();

				gpu.m_ticks -= 172;
			}
			break;

		default:
			break;
	}

}
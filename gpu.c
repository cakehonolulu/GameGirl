#include <gpu.h>
#include <int.h>

static uint64_t m_gpu_elapsed_ticks = 0;

m_gpu_t gpu;

void m_gpu_init()
{
	gpu.colors[0] = 0xFFFFFFFF;
    gpu.colors[1] = 0xFFC0C0C0;
    gpu.colors[2] = 0xFF606060;
    gpu.colors[3] = 0xFF000000;
}

void m_gpu_update_palette(uint8_t m_data)
{
	gpu.palette[3] = (m_data & 0xc0) >> 6;
	gpu.palette[2] = (m_data & 0x30) >> 4;
	gpu.palette[1] = (m_data & 0x0c) >> 2;
	gpu.palette[0] = (m_data & 0x03);
}

void m_gpu_step()
{
	if (m_cpu_ticks == 0)
	{
		gpu.m_ticks = 0;
		m_gpu_elapsed_ticks = 0;
	}
	
	gpu.m_ticks += m_cpu_ticks - m_gpu_elapsed_ticks;
	
	m_gpu_elapsed_ticks = m_cpu_ticks;

	printf("gpu.m_ticks: %ld, m_cpu_ticks: %ld, m_gpu_elapsed_ticks: %ld\n", gpu.m_ticks, m_cpu_ticks, m_gpu_elapsed_ticks);

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
				} else {
					gpu.m_stat = M_GPU_OAM;
				}

				gpu.m_ticks -= 204;
			}
			break;

		case M_GPU_VBLANK:
			if (gpu.m_ticks >= 456)
			{
				gpu.m_scanline++;		

				if (gpu.m_scanline > 153)
				{
					gpu.m_scanline = 0;
					gpu.m_stat = M_GPU_OAM;
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

				if (gpu.m_lcdc & GPU_CONTROL_DISPLAYENABLE) m_render_sc();

				gpu.m_ticks -= 172;
			}
			break;

		default:
			break;
	}

}

void m_gpu_update_tile(uint16_t m_addr)
{
	m_addr &= 0x1FFE;

	uint16_t tile = (m_addr >> 4) & 511;

	uint16_t y = (m_addr >> 1) & 7;

	uint8_t bitIndex;
	
	for (int x = 0; x < 8; x++)
	{
		bitIndex = 1 << (7 - x);

		gpu.tileset[tile][x][y] = (((mmu->gb_mmap.vram[m_addr]) & bitIndex) ? 1 : 0) + (((mmu->gb_mmap.vram[m_addr + 1]) & bitIndex) ? 2 : 0);
	}
}
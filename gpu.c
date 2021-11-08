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
					drawFramebuffer();
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

uint8_t tiles[512][8][8];

void updateTile(uint16_t address, uint8_t value) {
	address &= 0x1ffe;

	uint16_t tile = (address >> 4) & 511;

	uint16_t y = (address >> 1) & 7;

	if (value != 0)
	{
		printf("ADDR: 0x%04X, val: 0x%02X, tile: 0x%04X y: 0x%02X\n", address + 0x8000, mmu_read_byte(address + 0x8000), tile, y);
	}

	uint8_t bitIndex;

	for(int x = 0; x < 8; x++)
	{
		bitIndex = 1 << (7 - x);

		tiles[tile][x][y] = (((address + 0x8000) & bitIndex) ? 1 : 0) + ((((address + 1) + 0x8000) & bitIndex) ? 2 : 0);
	}
}
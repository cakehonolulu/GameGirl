#include <ppu.h>
#include <interrupts.h>

static uint64_t m_ppu_elapsed_ticks = 0;

m_ppu_t ppu;

void m_ppu_init()
{
#ifdef GAMEGIRL_DISPLAY_BW
	ppu.colors[0] = 0xFFFFFFFF;
    ppu.colors[1] = 0xFFC0C0C0;
    ppu.colors[2] = 0xFF606060;
    ppu.colors[3] = 0xFF000000;
#else
	ppu.colors[0] = 0x009BBC0F;
    ppu.colors[1] = 0x008BAC0F;
    ppu.colors[2] = 0x00306230;
    ppu.colors[3] = 0x000F380F;
#endif
}

void m_ppu_update_palette(uint8_t m_data)
{
	ppu.palette[3] = (m_data & 0xc0) >> 6;
	ppu.palette[2] = (m_data & 0x30) >> 4;
	ppu.palette[1] = (m_data & 0x0c) >> 2;
	ppu.palette[0] = (m_data & 0x03);
}

void m_ppu_step()
{
	ppu.m_ticks += m_cpu_ticks;// - m_ppu_elapsed_ticks;
	
	//m_ppu_elapsed_ticks = m_cpu_ticks;

	switch (ppu.m_stat)
	{
		case M_GPU_HBLANK:
			if (ppu.m_ticks >= 204)
			{
				ppu.m_scanline++;

				if (ppu.m_scanline == 143)
				{
					/*if (interrupts.m_enabled & INT_VBLANK)
					{
						interrupts.m_flags |= INT_VBLANK;*/
						ppu.m_stat = M_GPU_VBLANK;
					/*} else {
						ppu.m_cppu_mode = M_GPU_OAM;
						ppu.m_ticks -= 204;
					}*/
				} else {
					ppu.m_stat = M_GPU_OAM;
				}

				ppu.m_ticks -= 204;
			}
			break;

		case M_GPU_VBLANK:
			if (ppu.m_ticks >= 456)
			{
				ppu.m_scanline++;		

				if (ppu.m_scanline > 153)
				{
					ppu.m_scanline = 0;
					ppu.m_stat = M_GPU_OAM;
				}

				ppu.m_ticks -= 456;
			}
			break;

		case M_GPU_OAM:
			if (ppu.m_ticks >= 80)
			{
				ppu.m_stat = M_GPU_VRAM;
				
				ppu.m_ticks -= 80;
			}
			break;

		case M_GPU_VRAM:
			if (ppu.m_ticks >= 172)
			{
				ppu.m_stat = M_GPU_HBLANK;

				if (ppu.m_lcdc & GPU_CONTROL_DISPLAYENABLE) m_render_sc();

				ppu.m_ticks -= 172;
			}
			break;

		default:
			break;
	}

}

void m_ppu_update_tile(uint16_t m_addr)
{
	m_addr &= 0x1FFE;

	uint16_t tile = (m_addr >> 4) & 511;

	uint16_t y = (m_addr >> 1) & 7;

	uint8_t bitIndex;
	
	for (int x = 0; x < 8; x++)
	{
		bitIndex = 1 << (7 - x);

		ppu.tileset[tile][x][y] = (((mmu->gb_mmap.vram[m_addr]) & bitIndex) ? 1 : 0) + (((mmu->gb_mmap.vram[m_addr + 1]) & bitIndex) ? 2 : 0);
	}
}
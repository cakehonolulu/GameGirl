#include <ppu.h>
#include <interrupts.h>
#include <gamegirl.h>
#include <render.h>

void m_ppu_init(m_dmg_t *m_dmg)
{

	m_dmg->ppu = (m_ppu_t*)malloc(sizeof(m_ppu_t));

#ifdef GAMEGIRL_DISPLAY_BW
	m_dmg->ppu->colors[0] = 0xFFFFFFFF;
    m_dmg->ppu->colors[1] = 0xFFC0C0C0;
    m_dmg->ppu->colors[2] = 0xFF606060;
    m_dmg->ppu->colors[3] = 0xFF000000;
#else
	m_dmg->ppu->colors[0] = 0x009BBC0F;
    m_dmg->ppu->colors[1] = 0x008BAC0F;
    m_dmg->ppu->colors[2] = 0x00306230;
    m_dmg->ppu->colors[3] = 0x000F380F;
#endif
}

void m_ppu_update_palette(m_dmg_t *m_dmg, uint8_t m_data)
{
	m_dmg->ppu->palette[3] = (m_data & 0xc0) >> 6;
	m_dmg->ppu->palette[2] = (m_data & 0x30) >> 4;
	m_dmg->ppu->palette[1] = (m_data & 0x0c) >> 2;
	m_dmg->ppu->palette[0] = (m_data & 0x03);
}

void m_ppu_step(m_dmg_t *m_dmg, size_t m_cycles)
{
	m_dmg->ppu->m_ticks += m_cycles;
	
	switch (m_dmg->ppu->m_stat)
	{
		case M_GPU_HBLANK:
			if (m_dmg->ppu->m_ticks >= 204)
			{
				m_dmg->ppu->m_scanline++;

				if (m_dmg->ppu->m_scanline == 143)
				{
					if (m_dmg->m_speedhack) { if (m_dmg->ppu->m_lcdc & GPU_CONTROL_DISPLAYENABLE) m_sdl_draw_screen(m_dmg); }
					/*if (interrupts.m_enabled & INT_VBLANK)
					{
						interrupts.m_flags |= INT_VBLANK;*/
						m_dmg->ppu->m_stat = M_GPU_VBLANK;
					/*} else {
						m_dmg->ppu->m_cppu_mode = M_GPU_OAM;
						m_dmg->ppu->m_ticks -= 204;
					}*/
				} else {
					m_dmg->ppu->m_stat = M_GPU_OAM;
				}

				m_dmg->ppu->m_ticks -= 204;
			}
			break;

		case M_GPU_VBLANK:
			if (m_dmg->ppu->m_ticks >= 456)
			{
				m_dmg->ppu->m_scanline++;		

				if (m_dmg->ppu->m_scanline > 153)
				{
					m_dmg->ppu->m_scanline = 0;
					m_dmg->ppu->m_stat = M_GPU_OAM;
				}

				m_dmg->ppu->m_ticks -= 456;
			}
			break;

		case M_GPU_OAM:
			if (m_dmg->ppu->m_ticks >= 80)
			{
				m_dmg->ppu->m_stat = M_GPU_VRAM;
				
				m_dmg->ppu->m_ticks -= 80;
			}
			break;

		case M_GPU_VRAM:
			if (m_dmg->ppu->m_ticks >= 172)
			{
				m_dmg->ppu->m_stat = M_GPU_HBLANK;

				if (m_dmg->ppu->m_lcdc & GPU_CONTROL_DISPLAYENABLE) m_render_sc(m_dmg);

				m_dmg->ppu->m_ticks -= 172;
			}
			break;

		default:
			break;
	}

}

void m_ppu_update_tile(m_dmg_t *m_dmg, uint16_t m_addr)
{
	m_addr &= 0x1FFE;

	uint16_t tile = (m_addr >> 4) & 383;

	uint16_t y = (m_addr >> 1) & 7;

	uint8_t bitIndex;

	for (int x = 0; x < 8; x++)
	{
		bitIndex = 1 << (7 - x);

		m_dmg->ppu->tileset[tile][x][y] = (((m_dmg->m_memory->gb_mmap.vram[m_addr]) & bitIndex) ? 1 : 0) + (((m_dmg->m_memory->gb_mmap.vram[m_addr + 1]) & bitIndex) ? 2 : 0);
	}
}

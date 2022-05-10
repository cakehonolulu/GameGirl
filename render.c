#include <render.h>
#include <ppu.h>
#include <mmu.h>
#include <SDL2/SDL.h>

void m_sdl_draw_screen(m_dmg_t *m_dmg)
{
	SDL_UpdateTexture(m_dmg->m_texture, NULL, m_dmg->ppu->framebuffer, 160 * sizeof(uint32_t));
	SDL_RenderClear(m_dmg->m_renderer);
	SDL_RenderCopy(m_dmg->m_renderer, m_dmg->m_texture, NULL, NULL);
	SDL_RenderPresent(m_dmg->m_renderer);
}

void m_render_sc(m_dmg_t *m_dmg)
{
	int mapOffset = (m_dmg->ppu->m_lcdc & GPU_CONTROL_TILEMAP) ? 0x1c00 : 0x1800;
	mapOffset += (((m_dmg->ppu->m_scanline + m_dmg->ppu->m_verticalscroll) & 255) >> 3) << 5;

	uint8_t lineOffset = m_dmg->ppu->m_horitzontalscroll >> 3;

	uint8_t y = (m_dmg->ppu->m_scanline + m_dmg->ppu->m_verticalscroll) & 7;

	int8_t tile;
	uint32_t color;

	for(int x = 0; x < 160; x++)
	{
		tile = (int8_t)m_dmg->m_memory->gb_mmap.vram[mapOffset + lineOffset + (x / 8)];

		color = m_dmg->ppu->colors[m_dmg->ppu->palette[m_dmg->ppu->tileset[tile][x % 8][y]]];
		m_dmg->ppu->framebuffer[x + 160 * m_dmg->ppu->m_scanline] = color;
	}

}

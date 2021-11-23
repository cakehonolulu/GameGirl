#include <render.h>
#include <gpu.h>
#include <mmu.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <GL/gl.h>

extern SDL_Window   *m_window;
extern SDL_Renderer *m_renderer;
extern SDL_Texture *m_texture;

void drawFramebuffer()
{
	SDL_UpdateTexture(m_texture, NULL, gpu.framebuffer, 144 * sizeof(uint32_t));
	SDL_RenderClear(m_renderer);
	SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
	SDL_RenderPresent(m_renderer);
}

void m_render_sc()
{
	int mapOffset = (gpu.m_lcdc & GPU_CONTROL_TILEMAP) ? 0x1c00 : 0x1800;
	mapOffset += (((gpu.m_scanline + gpu.m_verticalscroll) & 255) >> 3) << 5;

	uint8_t lineOffset = gpu.m_horitzontalscroll >> 3;

	uint8_t x;
	uint8_t y = (gpu.m_scanline + gpu.m_verticalscroll) & 7;

	//printf("mapOffset = 0x%04X, lineOffset = 0x%04X, x = 0x%04X, y = 0x%04X, pixelOffset = 0x%04X\n", mapOffset, lineOffset, x, y, pixelOffset);

	int8_t tile;
	uint32_t color;

	//if (tile != 0) printf("Tile = 0x%02X\n", tile);

	for(int x = 0; x < 160; x++)
	{
		tile = (int8_t)mmu->gb_mmap.vram[mapOffset + lineOffset + (x / 8)];

		color = gpu.colors[gpu.palette[gpu.tileset[tile][x % 8][y]]];
		gpu.framebuffer[144 * gpu.m_scanline + x] = color;
	}

}
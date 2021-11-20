#include <render.h>
#include <gpu.h>
#include <mmu.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <GL/gl.h>

extern SDL_Window   *m_window;
extern SDL_Renderer *m_renderer;

void drawFramebuffer()
{
	int x, y;
	for (y = 0; y < 144; y++)
	{
		for (x = 0; x < 160; x++)
		{
			int col = gpu.framebuffer[x][y];

			SDL_SetRenderDrawColor(m_renderer, col >> 16, col >> 8, col, 0xff);
			SDL_RenderDrawPoint(m_renderer, x, y);
		}
	}

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
		gpu.framebuffer[x][gpu.m_scanline] = color;
	}

}
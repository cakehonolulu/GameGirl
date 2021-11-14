#include "include/render.h"
#include "include/gpu.h"
#include "include/mmu.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <GL/gl.h>

struct rgb framebuffer[160 * 144];
extern SDL_Window   *m_window;

const struct rgb palette[4] = {
	{ 255, 255, 255 },
	{ 192, 192, 192 },
	{ 96, 96, 96 },
	{ 0, 0, 0 },
};


void drawFramebuffer(void) {
	//framebuffer[50 * 160 + 50].r = 255;
	//framebuffer[50 * 160 + 50].g = 255;
	//framebuffer[50 * 160 + 50].b = 255;
glClear(GL_COLOR_BUFFER_BIT);
glRasterPos2f(-1, 1);
	glPixelZoom(1, -1);
	glDrawPixels(160, 144, GL_RGB, GL_UNSIGNED_BYTE, framebuffer);
		SDL_GL_SwapWindow(m_window);

}

void m_render_sc()
{
	// LCDC ($FF40) Bit 3 - BG Tile Map Display Select -> (1=9C00-9FFF), 0=9800-9BFF)
	uint16_t m_gpu_tilemap = (gpu.m_lcdc & GPU_CONTROL_TILEMAP) ? 0x1C00 : 0x1800;



	uint16_t mapOffset = m_gpu_tilemap + ((((gpu.m_scanline + gpu.m_verticalscroll) & 255) >> 3) << 5);

	uint8_t lineOffset = (gpu.m_horitzontalscroll >> 3);

	uint8_t x;

	int y = (gpu.m_scanline + gpu.m_verticalscroll) & 7;

	int pixelOffset = gpu.m_scanline * 160;


	uint8_t tile;

	uint8_t my = (y + gpu.m_scanline);

	uint16_t tile_row = ((uint8_t)(y/8));

	int i;
	
	for(i = 0; i < 160; i++)
	{
		tile = (uint8_t)mmu->gb_mmap.vram[mapOffset + lineOffset];

		framebuffer[pixelOffset].r = palette[tiles[tile][x][y]].r;
		framebuffer[pixelOffset].g = palette[tiles[tile][x][y]].g;
		framebuffer[pixelOffset].b = palette[tiles[tile][x][y]].b;

		pixelOffset++;

		x++;

		if(x == 8)
		{
			x = 0;
			lineOffset = (lineOffset + 1) & 31;
			

			tile = (uint8_t)mmu->gb_mmap.vram[mapOffset + lineOffset];
		}
	}
}
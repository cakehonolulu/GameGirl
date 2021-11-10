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


	// LCDC ($FF40) Bit 4 - BG & Window Tile Data Select -> (1=8000-8FFF, 0=8800-97FF)
	uint16_t m_gpu_tileset = (gpu.m_lcdc & GPU_CONTROL_TILESET) ? 0x0000 : 0x0800;

	uint16_t m_gpu_tileaddr = (m_gpu_tilemap + ((((gpu.m_scanline + gpu.m_verticalscroll) & 255) >> 3) << 5));

	uint8_t m_gpu_tilenumber = (uint8_t) (m_gpu_tileaddr >> 8);

	//printf("tile 0x%04X map: 0x%02X\n", m_gpu_tileaddr, m_gpu_tilenumber);

	int lineOffset = (gpu.m_horitzontalscroll >> 3);

	printf("Mapping: 0x%04X\n", m_gpu_tileaddr);

	int x = gpu.m_horitzontalscroll & 7;
	int y = (gpu.m_scanline + gpu.m_verticalscroll) & 7;

	int pixelOffset = gpu.m_scanline * 160;


	unsigned short tile = (unsigned short)mmu->gb_mmap.vram[((m_gpu_tileaddr & 0xFF00) >> 4) + lineOffset];


	//printf("Tile: %02X\n", tile);

	

	int i;
	
	for(i = 0; i < 160; i++)
	{
		framebuffer[pixelOffset].r = palette[tiles[m_gpu_tilenumber][x][y]].r;
		framebuffer[pixelOffset].g = palette[tiles[m_gpu_tilenumber][x][y]].g;
		framebuffer[pixelOffset].b = palette[tiles[m_gpu_tilenumber][x][y]].b;

		pixelOffset++;

		x++;

		if(x == 8)
		{
			x = 0;
			lineOffset = (lineOffset + 1) & 31;
			

			tile = (uint16_t) mmu->gb_mmap.vram[((m_gpu_tileaddr & 0xFF00) >> 4) + lineOffset];
		}
	}
}
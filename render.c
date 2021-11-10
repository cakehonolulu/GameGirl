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
	int mapOffset = (gpu.m_lcdc & GPU_CONTROL_TILEMAP) ? 0x1C00 : 0x1800;

	int mapping = (mapOffset + ((((gpu.m_scanline + gpu.m_verticalscroll) & 255) >> 3) << 5));

	int lineOffset = gpu.m_horitzontalscroll >> 3;

	int x = gpu.m_horitzontalscroll & 7;
	int y = (gpu.m_scanline + gpu.m_verticalscroll) & 7;

	int pixelOffset = gpu.m_scanline * 160;

	unsigned char tile = 0x0019;

	int i;
	for(i = 0; i < 160; i++) {
		framebuffer[pixelOffset].r = palette[tiles[tile][x][y]].r;
		framebuffer[pixelOffset].g = palette[tiles[tile][x][y]].g;
		framebuffer[pixelOffset].b = palette[tiles[tile][x][y]].b;
		pixelOffset++;

		x++;
		if(x == 8) {
			x = 0;
			lineOffset = (lineOffset + 1) & 31;
			tile = mmu->gb_mmap.vram[mapping + lineOffset];
		}
	}
}
#include "../lib/libk.h"

#define VESA_ADDRESS 0xE0000000
#define VESA_WIDTH 1024
#define VESA_HEIGHT 768
#define VESA_BPP 32

static uint32_t *framebuffer = (uint32_t *)VESA_ADDRESS;

void fill_screen(uint32_t color) {
    for (int i = 0; i < VESA_WIDTH * VESA_HEIGHT; i++) {
        framebuffer[i] = color;
    }
}

void put_pixel(int x, int y, uint32_t color) {
    if (x >= 0 && x < VESA_WIDTH && y >= 0 && y < VESA_HEIGHT) {
        framebuffer[y * VESA_WIDTH + x] = color;
    }
}

void draw_rect(int x, int y, int w, int h, uint32_t color) {
    for (int i = y; i < y + h; i++) {
        for (int j = x; j < x + w; j++) {
            put_pixel(j, i, color);
        }
    }
}

void draw_line(int x0, int y0, int x1, int y1, uint32_t color) {
    int dx = (x1 > x0) ? (x1 - x0) : (x0 - x1);
    int dy = (y1 > y0) ? (y1 - y0) : (y0 - y1);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;
    
    while (1) {
        put_pixel(x0, y0, color);
        if (x0 == x1 && y0 == y1) break;
        
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}

void graphics_init() {
    fill_screen(0x001F3A);
}

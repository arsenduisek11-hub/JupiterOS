#ifndef VIDEO_H
#define VIDEO_H

#include "../include/types.h"

#define SCREEN_W 1024
#define SCREEN_H 768

void video_init();
void video_clear(uint32_t color);
void video_pixel(int x, int y, uint32_t color);
void video_rect(int x, int y, int w, int h, uint32_t color);
void video_rect_outline(int x, int y, int w, int h, uint32_t color);
void video_draw_char(char c, int x, int y, uint32_t color);
void video_draw_str(char* s, int x, int y, uint32_t color);

#endif

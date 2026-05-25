#ifndef WINDOW_H
#define WINDOW_H

#include "../include/types.h"

typedef struct {
    int x, y, w, h;
    char title[32];
    int active;
    int win_id;
} Window;

int window_create(char* title, int x, int y, int w, int h);
void window_draw(Window* w);
void window_close(int win_id);
void window_set_active(int win_id);
int window_handle_click(int x, int y);
void window_update_drag(int x, int y);

#endif

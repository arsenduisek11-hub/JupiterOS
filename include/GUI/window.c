// оконный менеджер - ебаный рот
// перетаскивание, z-order, закрытие

#include "../include/types.h"
#include "../kernel/video.h"
#include "window.h"

#define MAX_WINDOWS 32

static Window windows[MAX_WINDOWS];
static int window_count = 0;
static int active_window = -1;
static int drag_window = -1;
static int drag_offx = 0, drag_offy = 0;

int window_create(char* title, int x, int y, int w, int h) {
    if(window_count >= MAX_WINDOWS) return -1;
    
    windows[window_count].x = x;
    windows[window_count].y = y;
    windows[window_count].w = w;
    windows[window_count].h = h;
    windows[window_count].active = 1;
    windows[window_count].win_id = window_count;
    
    for(int i = 0; i < 32 && title[i]; i++)
        windows[window_count].title[i] = title[i];
    
    if(active_window != -1)
        windows[active_window].active = 0;
    active_window = window_count;
    
    window_count++;
    return window_count - 1;
}

void window_draw(Window* w) {
    // тело
    video_rect(w->x, w->y, w->w, w->h, 0x1E1E2A);
    // заголовок
    video_rect(w->x, w->y, w->w, 28, w->active ? 0x7C3AED : 0x3A3A4A);
    // рамка
    video_rect_outline(w->x, w->y, w->w, w->h, 0x7C3AED);
    // крестик
    video_rect(w->x + w->w - 24, w->y + 4, 20, 20, 0xEF4444);
    video_rect_outline(w->x + w->w - 24, w->y + 4, 20, 20, 0xFFFFFF);
    video_draw_str("X", w->x + w->w - 19, w->y + 8, 0xFFFFFF);
    // заголовок
    video_draw_str(w->title, w->x + 8, w->y + 8, 0xFFFFFF);
}

void window_close(int win_id) {
    if(win_id < 0 || win_id >= window_count) return;
    
    for(int i = win_id; i < window_count - 1; i++)
        windows[i] = windows[i + 1];
    window_count--;
    
    if(active_window == win_id) active_window = -1;
    if(window_count > 0) {
        active_window = 0;
        windows[0].active = 1;
    }
}

int window_handle_click(int x, int y) {
    for(int i = window_count - 1; i >= 0; i--) {
        Window* w = &windows[i];
        if(x >= w->x && x <= w->x + w->w && y >= w->y && y <= w->y + w->h) {
            // крестик
            if(x >= w->x + w->w - 24 && x <= w->x + w->w - 4 &&
               y >= w->y + 4 && y <= w->y + 24) {
                window_close(i);
                return 1;
            }
            // заголовок - таскаем
            if(y <= w->y + 28) {
                drag_window = i;
                drag_offx = x - w->x;
                drag_offy = y - w->y;
            }
            // поднимаем окно
            if(i != active_window) {
                Window tmp = windows[i];
                for(int j = i; j < active_window; j++)
                    windows[j] = windows[j + 1];
                windows[active_window] = tmp;
                for(int j = 0; j < window_count; j++)
                    windows[j].active = (j == window_count - 1);
                active_window = window_count - 1;
            }
            return 1;
        }
    }
    return 0;
}

void window_update_drag(int x, int y) {
    if(drag_window != -1) {
        windows[drag_window].x = x - drag_offx;
        windows[drag_window].y = y - drag_offy;
    }
}

void window_stop_drag() {
    drag_window = -1;
}

int window_get_active() {
    return active_window;
}

int window_get_count() {
    return window_count;
}

Window* window_get(int i) {
    if(i >= 0 && i < window_count) return &windows[i];
    return NULL;
}

// графика в сборе - все вместе

#include "../include/types.h"
#include "../kernel/video.h"
#include "../kernel/mouse.h"
#include "gui.h"
#include "window.h"
#include "cursor.h"
#include "taskbar.h"
#include "desktop.h"

static int drag_active = 0;

void gui_init() {
    cursor_init();
    taskbar_init();
    desktop_init();
    
    // тестовое окошко приветствия
    window_create("Welcome", 200, 150, 300, 200);
}

void gui_update() {
    static int prev_mouse_down = 0;
    int mouse_down = mouse_button_left();
    
    // обработка кликов
    if(mouse_down && !prev_mouse_down) {
        int x = mouse_get_x();
        int y = mouse_get_y();
        
        // сначала окна
        int handled = window_handle_click(x, y);
        if(!handled) {
            // потом десктоп
            desktop_click(x, y);
        }
    }
    
    // обновление перетаскивания
    if(mouse_down) {
        window_update_drag(mouse_get_x(), mouse_get_y());
    } else {
        window_stop_drag();
    }
    
    prev_mouse_down = mouse_down;
    
    // отрисовка
    video_clear(0x0A0A14);
    
    // окна
    for(int i = 0; i < window_get_count(); i++) {
        Window* w = window_get(i);
        if(w) window_draw(w);
    }
    
    desktop_draw();
    taskbar_draw();
    cursor_draw(mouse_get_x(), mouse_get_y());
}
// Наконец  все закончилось то

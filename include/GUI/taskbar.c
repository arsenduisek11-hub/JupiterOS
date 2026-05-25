// панель задач снизу
// показывает кнопки окон и часы (которые не идут)

#include "../include/types.h"
#include "../kernel/video.h"
#include "taskbar.h"
#include "window.h"

static int taskbar_height = 40;

void taskbar_init() {
    // нихуя не надо
}

void taskbar_draw() {
    int y = SCREEN_H - taskbar_height;
    
    video_rect(0, y, SCREEN_W, taskbar_height, 0x1A1A2A);
    video_rect_outline(0, y, SCREEN_W, taskbar_height, 0x7C3AED);
    
    // кнопка пуск
    video_rect(4, y + 4, 60, 32, 0x7C3AED);
    video_draw_str("Пуск", 12, y + 12, 0xFFFFFF);
    
    // кнопки окон
    int offset = 72;
    for(int i = 0; i < window_get_count(); i++) {
        Window* w = window_get(i);
        if(w) {
            uint32_t color = w->active ? 0x7C3AED : 0x3A3A4A;
            video_rect(offset, y + 4, 100, 32, color);
            video_draw_str(w->title, offset + 8, y + 12, 0xFFFFFF);
            offset += 108;
        }
    }
    
    // часы (время не получаем, пишем хуйню)
    video_draw_str("23:59", SCREEN_W - 60, y + 12, 0xFFFFFF);
}

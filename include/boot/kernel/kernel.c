// JupiterOS kernel - main entry point
// Арсен 12 лет, Казахстан
// матерюсь потому что могу

#include "../include/types.h"
#include "memory.h"
#include "keyboard.h"
#include "mouse.h"
#include "video.h"
#include "fs.h"
#include "../gui/gui.h"

void kmain() {
    // чистим хуйню
    video_clear(0x0A0A14);
    
    video_draw_str("JupiterOS v1.0", 10, 10, 0x7C3AED);
    video_draw_str("Arsen 12 years, Kazakhstan", 10, 40, 0xA855F7);
    video_draw_str("Loading...", 10, 70, 0xFFFFFF);
    
    // инициализируем всё говно
    keyboard_init();
    mouse_init();
    fs_init();
    gui_init();
    
    video_draw_str("Ready. Click icons.", 10, 100, 0x10B981);
    
    // бесконечный цикл, как моя жизнь
    while(1) {
        gui_update();
        for(int i = 0; i < 100000; i++) __asm__("pause");
    }
}

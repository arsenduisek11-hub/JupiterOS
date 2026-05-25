// рабочий стол - иконки и запуск приложений
// двойной клик? нахуй, простой клик

#include "../include/types.h"
#include "../kernel/video.h"
#include "../kernel/fs.h"
#include "desktop.h"
#include "window.h"
#include "../apps/browser.h"
#include "../apps/editor.h"

typedef struct {
    int x, y;
    char name[16];
    void (*on_click)();
} DesktopIcon;

static DesktopIcon icons[] = {
    {20, 20, "Браузер", browser_open},
    {20, 70, "J-Code", editor_open},
    {20, 120, "Файлы", fs_list_files},
};

static int icon_count = 3;

void desktop_init() {
    // ебать
}

void desktop_draw() {
    for(int i = 0; i < icon_count; i++) {
        video_rect(icons[i].x, icons[i].y, 60, 40, 0x1E1E2A);
        video_rect_outline(icons[i].x, icons[i].y, 60, 40, 0x7C3AED);
        video_draw_str(icons[i].name, icons[i].x + 4, icons[i].y + 24, 0xFFFFFF);
    }
}

void desktop_click(int x, int y) {
    for(int i = 0; i < icon_count; i++) {
        if(x >= icons[i].x && x <= icons[i].x + 60 &&
           y >= icons[i].y && y <= icons[i].y + 40) {
            if(icons[i].on_click) icons[i].on_click();
            return;
        }
    }
}

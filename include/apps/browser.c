// Pizda
// браузер - HTTP GET, парсинг простых тегов
// без картинок, без CSS, но работает

#include "../include/types.h"
#include "../gui/window.h"
#include "../kernel/video.h"
#include "../kernel/fs.h"

static int browser_win = -1;
static char current_url[256] = "example.com";

void http_get(char* host, char* response, int max_len) {
    // реальный HTTP запрос в ядре не реализован
    // потому что сетевой драйвер - это пиздец
    // пока заглушка
    char* fake_response = "<html><body><h1>Hello JupiterOS</h1><p>This is a browser.<br>Network driver coming soon.</p></body></html>";
    int i = 0;
    while(fake_response[i] && i < max_len - 1) {
        response[i] = fake_response[i];
        i++;
    }
    response[i] = 0;
}

void browser_render(char* html, int x, int y) {
    // простой парсинг - вырезаем теги
    char text[4096];
    int in_tag = 0;
    int pos = 0;
    
    for(int i = 0; html[i] && pos < 4095; i++) {
        if(html[i] == '<') {
            in_tag = 1;
        } else if(html[i] == '>') {
            in_tag = 0;
        } else if(!in_tag && html[i] != '\n' && html[i] != '\r') {
            text[pos++] = html[i];
        }
    }
    text[pos] = 0;
    
    video_draw_str(text, x + 10, y + 40, 0xFFFFFF);
}

void browser_open() {
    if(browser_win != -1) {
        window_close(browser_win);
    }
    
    browser_win = window_create("J-Browser", 80, 60, 800, 550);
    
    // рисуем интерфейс
    Window* w = window_get(window_get_active());
    if(w) {
        // адресная строка
        video_rect(w->x + 10, w->y + 32, 600, 24, 0x2A2A3A);
        video_draw_str(current_url, w->x + 15, w->y + 38, 0xFFFFFF);
        
        // кнопка GO
        video_rect(w->x + 620, w->y + 32, 50, 24, 0x7C3AED);
        video_draw_str("GO", w->x + 635, w->y + 38, 0xFFFFFF);
        
        // загружаем страницу
        char response[4096];
        http_get(current_url, response, 4096);
        browser_render(response, w->x, w->y);
    }
}

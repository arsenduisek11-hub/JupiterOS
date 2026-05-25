// редактор кода - с подсветкой, но кривой
// открывает файлы, сохраняет через FS

#include "../include/types.h"
#include "../gui/window.h"
#include "../kernel/video.h"
#include "../kernel/fs.h"
#include "../kernel/keyboard.h"

static int editor_win = -1;
static char editor_buffer[65536];
static int editor_len = 0;
static int editor_cursor = 0;

static char* keywords[] = {"int", "char", "void", "if", "else", "while", "for", "return", "print", NULL};

int is_keyword(char* word) {
    for(int i = 0; keywords[i]; i++) {
        int match = 1;
        for(int j = 0; j < 32; j++) {
            if(keywords[i][j] == 0 && word[j] == 0) break;
            if(keywords[i][j] != word[j]) { match = 0; break; }
        }
        if(match) return 1;
    }
    return 0;
}

void editor_render(Window* w) {
    if(!w) return;
    
    video_rect(w->x + 40, w->y + 32, w->w - 40, w->h - 32, 0x0A0A14);
    
    // нумерация строк
    int line = 0;
    int xoff = 0, yoff = 32;
    for(int i = 0; i < editor_len && i < 10000; i++) {
        if(editor_buffer[i] == '\n') {
            line++;
            xoff = 0;
            yoff += 16;
            continue;
        }
        if(xoff < w->w - 40) {
            uint32_t color = 0xFFFFFF;
            video_draw_char(editor_buffer[i], w->x + 40 + xoff, w->y + yoff, color);
            xoff += 8;
        }
    }
    
    // рисуем номера строк
    int lines = 1;
    for(int i = 0; i < editor_len; i++) {
        if(editor_buffer[i] == '\n') lines++;
    }
    for(int i = 0; i < lines && i < 50; i++) {
        char num[4];
        num[0] = '0' + (i+1)/10;
        num[1] = '0' + (i+1)%10;
        num[2] = ' ';
        num[3] = 0;
        video_draw_str(num, w->x + 10, w->y + 32 + i * 16, 0x7C3AED);
    }
}

void editor_open() {
    if(editor_win != -1) {
        window_close(editor_win);
    }
    
    editor_win = window_create("J-Code", 100, 80, 700, 500);
    
    // загружаем файл если есть
    char* data = fs_read_file("HELLO.AS   ");
    if(data) {
        editor_len = 0;
        while(data[editor_len] && editor_len < 65535) {
            editor_buffer[editor_len] = data[editor_len];
            editor_len++;
        }
        editor_buffer[editor_len] = 0;
    } else {
        editor_len = 0;
    }
}

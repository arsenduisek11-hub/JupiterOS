// FAT32? да ну нахуй
// пока просто массив файлов в памяти

#include "../include/types.h"
#include "fs.h"
#include "video.h"

typedef struct {
    char name[12];
    char* data;
    int size;
} File;

static File files[16];
static int file_count = 0;

void fs_init() {
    file_count = 3;
    
    // файл 1
    char* name1 = "README.TXT";
    for(int i = 0; i <= 11; i++) files[0].name[i] = name1[i];
    files[0].data = "JupiterOS v1.0\nCreated by Arsen, 12 years old\nKazakhstan\n";
    files[0].size = 48;
    
    // файл 2
    char* name2 = "HELLO.AS";
    for(int i = 0; i <= 11; i++) files[1].name[i] = name2[i];
    files[1].data = "print('Hello from ArsenScript!');\n";
    files[1].size = 34;
    
    // файл 3
    char* name3 = "CONFIG.CFG";
    for(int i = 0; i <= 11; i++) files[2].name[i] = name3[i];
    files[2].data = "theme=dark\nresolution=1024x768\n";
    files[2].size = 33;
}

char* fs_read_file(char* name) {
    for(int i = 0; i < file_count; i++) {
        int match = 1;
        for(int j = 0; j < 11; j++) {
            if(files[i].name[j] != name[j]) {
                match = 0;
                break;
            }
        }
        if(match) return files[i].data;
    }
    return NULL;
}

void fs_list_files() {
    video_draw_str("Files:", 20, 200, 0x7C3AED);
    for(int i = 0; i < file_count; i++) {
        video_draw_str(files[i].name, 30, 220 + i * 20, 0xFFFFFF);
    }
}

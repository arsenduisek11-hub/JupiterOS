// клавиатура - scancode в ascii
// set 2, потому что set 1 я не вывез

#include "../include/types.h"
#include "keyboard.h"

static char key_buffer[256];
static int buffer_head = 0;
static int buffer_tail = 0;

static const char scancode_to_ascii[] = {
    0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', 0,
    0, 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', 0,
    0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0,
    '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' '
};

void keyboard_init() {
    // лень, пусть работает как есть
}

static void keyboard_handler(uint8_t scancode) {
    if(scancode & 0x80) return; // release, похуй
    char c = scancode_to_ascii[scancode];
    if(c) {
        key_buffer[buffer_head] = c;
        buffer_head = (buffer_head + 1) % 256;
    }
}

char keyboard_getchar() {
    if(buffer_head == buffer_tail) return 0;
    char c = key_buffer[buffer_tail];
    buffer_tail = (buffer_tail + 1) % 256;
    return c;
}

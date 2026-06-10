#include "../lib/libk.h"

#define KEYBOARD_DATA 0x60
#define KEYBOARD_STATUS 0x64
#define KEYBOARD_CMD 0x64

static uint8_t keyboard_buffer[256];
static int kb_read = 0;
static int kb_write = 0;

extern uint8_t asm_inb(uint16_t port);
extern void asm_outb(uint16_t port, uint8_t value);

void keyboard_irq_handler() {
    uint8_t scancode = asm_inb(KEYBOARD_DATA);
    keyboard_buffer[kb_write] = scancode;
    kb_write = (kb_write + 1) % 256;
}

uint8_t keyboard_getchar() {
    while (kb_read == kb_write);
    uint8_t c = keyboard_buffer[kb_read];
    kb_read = (kb_read + 1) % 256;
    return c;
}

void keyboard_init() {
    kb_read = 0;
    kb_write = 0;
}

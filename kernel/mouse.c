#include "../lib/libk.h"

#define MOUSE_DATA 0x60
#define MOUSE_STATUS 0x64
#define MOUSE_CMD 0x64

struct mouse_state {
    int x;
    int y;
    uint8_t buttons;
} mouse;

extern uint8_t asm_inb(uint16_t port);
extern void asm_outb(uint16_t port, uint8_t value);

void mouse_irq_handler(uint8_t data) {
    static uint8_t mouse_data[3];
    static int mouse_data_index = 0;
    
    mouse_data[mouse_data_index] = data;
    mouse_data_index++;
    
    if (mouse_data_index == 3) {
        mouse.buttons = mouse_data[0] & 0x07;
        mouse.x += (int8_t)mouse_data[1];
        mouse.y -= (int8_t)mouse_data[2];
        
        if (mouse.x < 0) mouse.x = 0;
        if (mouse.y < 0) mouse.y = 0;
        if (mouse.x > 1024) mouse.x = 1024;
        if (mouse.y > 768) mouse.y = 768;
        
        mouse_data_index = 0;
    }
}

void mouse_init() {
    mouse.x = 512;
    mouse.y = 384;
    mouse.buttons = 0;
}

struct mouse_state *mouse_get_state() {
    return &mouse;
}

#include "../lib/libk.h"

#define VGA_ADDRESS 0xB8000
#define VGA_WIDTH 80
#define VGA_HEIGHT 25

static volatile uint16_t *vga_buffer = (uint16_t *)VGA_ADDRESS;
static uint32_t cursor_row = 0;
static uint32_t cursor_col = 0;

void clear_screen() {
    for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++) {
        vga_buffer[i] = 0x0F00;
    }
    cursor_row = 0;
    cursor_col = 0;
}

void putchar(char c) {
    if (c == '\n') {
        cursor_row++;
        cursor_col = 0;
    } else {
        vga_buffer[cursor_row * VGA_WIDTH + cursor_col] = 0x0F00 | c;
        cursor_col++;
    }
    
    if (cursor_col >= VGA_WIDTH) {
        cursor_col = 0;
        cursor_row++;
    }
    
    if (cursor_row >= VGA_HEIGHT) {
        cursor_row = VGA_HEIGHT - 1;
        for (int i = 0; i < VGA_HEIGHT - 1; i++) {
            for (int j = 0; j < VGA_WIDTH; j++) {
                vga_buffer[i * VGA_WIDTH + j] = vga_buffer[(i + 1) * VGA_WIDTH + j];
            }
        }
        for (int i = 0; i < VGA_WIDTH; i++) {
            vga_buffer[(VGA_HEIGHT - 1) * VGA_WIDTH + i] = 0x0F00;
        }
    }
}

void kernel_main(uint32_t magic, uint32_t mbi) {
    clear_screen();
    
    const char *msg = "JupiterOS v2.0 - 64-bit Kernel";
    while (*msg) {
        putchar(*msg++);
    }
    putchar('\n');
    
    printf("\nKernel initialized successfully\n");
    printf("Memory: 64 MB allocated\n");
    printf("CPU: x86-64\n");
    printf("Architecture: Multiboot\n");
    printf("Magic: %x\n", magic);
    
    while (1) {
        asm("hlt");
    }
}

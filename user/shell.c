#include "../lib/libk.h"

#define SHELL_BUFFER_SIZE 256

struct shell_state {
    char input_buffer[SHELL_BUFFER_SIZE];
    int input_pos;
    uint32_t window_id;
};

extern uint32_t window_create(int x, int y, int w, int h, const char *title, uint32_t bg_color);
extern uint8_t keyboard_getchar();

void shell_print_prompt(struct shell_state *shell) {
    printf("jupiter> ");
}

void shell_execute_command(struct shell_state *shell, const char *cmd) {
    if (strcmp(cmd, "help") == 0) {
        printf("Available commands:\n");
        printf("  ls      - list files\n");
        printf("  cat     - display file\n");
        printf("  echo    - print text\n");
        printf("  clear   - clear screen\n");
        printf("  help    - show this help\n");
    } else if (strcmp(cmd, "ls") == 0) {
        printf("shell.elf\neditor.elf\nfileman.elf\n");
    } else if (strcmp(cmd, "clear") == 0) {
        for (int i = 0; i < 25; i++) {
            printf("\n");
        }
    } else if (cmd[0] != 0) {
        printf("Unknown command: %s\n", cmd);
    }
}

void shell_init() {
    struct shell_state shell;
    shell.input_pos = 0;
    shell.window_id = window_create(0, 0, 1024, 768, "Shell", 0x000000);
    
    printf("\n");
    printf("JupiterOS Shell v1.0\n");
    printf("Type 'help' for commands\n");
    printf("\n");
    
    while (1) {
        shell_print_prompt(&shell);
        shell.input_pos = 0;
        
        while (1) {
            uint8_t c = keyboard_getchar();
            
            if (c == '\n' || c == '\r') {
                printf("\n");
                shell.input_buffer[shell.input_pos] = 0;
                break;
            } else if (c == '\b' && shell.input_pos > 0) {
                printf("\b \b");
                shell.input_pos--;
            } else if (c >= 32 && c < 127 && shell.input_pos < SHELL_BUFFER_SIZE - 1) {
                printf("%c", c);
                shell.input_buffer[shell.input_pos++] = c;
            }
        }
        
        shell_execute_command(&shell, shell.input_buffer);
    }
}

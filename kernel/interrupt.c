#include "../lib/libk.h"

#define MAX_INTERRUPTS 256

typedef void (*interrupt_handler_t)(uint32_t irq);

static interrupt_handler_t interrupt_handlers[MAX_INTERRUPTS];

void interrupt_register(uint32_t irq, interrupt_handler_t handler) {
    if (irq < MAX_INTERRUPTS) {
        interrupt_handlers[irq] = handler;
    }
}

void interrupt_handle(uint32_t irq) {
    if (irq < MAX_INTERRUPTS && interrupt_handlers[irq]) {
        interrupt_handlers[irq](irq);
    }
}

void interrupt_init() {
    for (int i = 0; i < MAX_INTERRUPTS; i++) {
        interrupt_handlers[i] = 0;
    }
}

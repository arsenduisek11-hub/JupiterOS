#include "../lib/libk.h"

#define PIC1_CMD 0x20
#define PIC1_DATA 0x21
#define PIC2_CMD 0xA0
#define PIC2_DATA 0xA1
#define ICW1 0x11
#define ICW4 0x01

struct idt_entry {
    uint16_t offset_lo;
    uint16_t selector;
    uint8_t zero;
    uint8_t type_attr;
    uint16_t offset_hi;
    uint32_t offset_64;
    uint32_t reserved;
};

struct idt_ptr {
    uint16_t limit;
    uint64_t base;
};

static struct idt_entry idt[256];
static struct idt_ptr idtr;

extern void asm_lidt(struct idt_ptr *ptr);
extern void asm_outb(uint16_t port, uint8_t value);
extern uint8_t asm_inb(uint16_t port);
extern void asm_sti();
extern void asm_cli();

void idt_set_entry(uint8_t num, uint64_t offset, uint16_t selector, uint8_t type) {
    idt[num].offset_lo = offset & 0xFFFF;
    idt[num].offset_hi = (offset >> 16) & 0xFFFF;
    idt[num].offset_64 = (offset >> 32) & 0xFFFFFFFF;
    idt[num].selector = selector;
    idt[num].zero = 0;
    idt[num].type_attr = type;
    idt[num].reserved = 0;
}

void pic_remap() {
    asm_outb(PIC1_CMD, ICW1);
    asm_outb(PIC2_CMD, ICW1);
    asm_outb(PIC1_DATA, 0x20);
    asm_outb(PIC2_DATA, 0x28);
    asm_outb(PIC1_DATA, 0x04);
    asm_outb(PIC2_DATA, 0x02);
    asm_outb(PIC1_DATA, ICW4);
    asm_outb(PIC2_DATA, ICW4);
    asm_outb(PIC1_DATA, 0);
    asm_outb(PIC2_DATA, 0);
}

void idt_init() {
    memset(idt, 0, sizeof(idt));
    idtr.limit = sizeof(idt) - 1;
    idtr.base = (uint64_t)&idt[0];
    asm_lidt(&idtr);
}

void irq_handler(int irq) {
    if (irq >= 8) {
        asm_outb(PIC2_CMD, 0x20);
    }
    asm_outb(PIC1_CMD, 0x20);
}

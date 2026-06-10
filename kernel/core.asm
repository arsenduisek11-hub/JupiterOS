section .text
global asm_lgdt
global asm_lidt
global asm_outb
global asm_inb
global asm_sti
global asm_cli
global asm_hlt

asm_lgdt:
    lgdt [rdi]
    ret

asm_lidt:
    lidt [rdi]
    ret

asm_outb:
    mov al, sil
    out dx, al
    ret

asm_inb:
    in al, dx
    ret

asm_sti:
    sti
    ret

asm_cli:
    cli
    ret

asm_hlt:
    hlt
    ret

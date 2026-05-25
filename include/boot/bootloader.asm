; jupiterOS bootloader
; писал ночью, бухал чай, работает сука

section .multiboot
align 4
    dd 0x1BADB002          ; магия
    dd 0x03                ; флаги
    dd -(0x1BADB002 + 0x03) ; контрольная сумма, ебать

section .text
global _start
extern kmain

_start:
    mov esp, stack_top
    push ebx
    push eax
    call kmain
    cli
.hang:
    hlt
    jmp .hang

section .bss
align 16
stack_bottom:
    resb 16384
stack_top:

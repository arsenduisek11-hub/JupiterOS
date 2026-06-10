MULTIBOOT_MAGIC equ 0x1BADB002
MULTIBOOT_FLAGS equ 0x00000003
MULTIBOOT_CHECKSUM equ -(MULTIBOOT_MAGIC + MULTIBOOT_FLAGS)

section .multiboot
align 4
    dd MULTIBOOT_MAGIC
    dd MULTIBOOT_FLAGS
    dd MULTIBOOT_CHECKSUM

section .bss
align 4096
bootstrap_page_table:
    resb 4096
bootstrap_page_dir:
    resb 4096
bootstrap_pdpt:
    resb 4096
bootstrap_pml4:
    resb 4096

bootstrap_stack:
    resb 16384

section .text
global _start
extern kernel_main

_start:
    cli
    
    mov esp, bootstrap_stack + 16384
    
    mov eax, bootstrap_pml4 - 0xC0000000
    mov cr3, eax
    
    mov eax, cr4
    or eax, 0x00000020
    mov cr4, eax
    
    mov ecx, 0xC0000080
    rdmsr
    or eax, 0x00000100
    wrmsr
    
    mov eax, cr0
    or eax, 0x80000001
    mov cr0, eax
    
    lgdt [gdtr]
    jmp 0x08:long_mode

gdtr:
    dw gdt_end - gdt - 1
    dq gdt - 0xC0000000

gdt:
    dq 0x0000000000000000
    dq 0x00209a0000000000
    dq 0x0020920000000000
    dq 0x00209a0000000000
    dq 0x0020920000000000
gdt_end:

bits 64
long_mode:
    xor rax, rax
    mov rax, kernel_main
    call rax
    cli
    hlt

CC = x86_64-elf-gcc
AS = nasm
LD = x86_64-elf-ld
OBJCOPY = x86_64-elf-objcopy

CFLAGS = -ffreestanding -fno-stack-protector -fno-builtin -Wall -Wextra -O2 -m64 -fPIC
ASFLAGS = -f elf64
LDFLAGS = -T linker.ld -nostdlib

SOURCES_C = kernel/kernel.c lib/libk.c
SOURCES_ASM = boot/boot.asm

OBJECTS_C = $(SOURCES_C:.c=.o)
OBJECTS_ASM = $(SOURCES_ASM:.asm=.o)
OBJECTS = $(OBJECTS_C) $(OBJECTS_ASM)

KERNEL = build/kernel.bin
ISO = build/jupiteros.iso

.PHONY: all clean run run-kvm iso

all: $(KERNEL)

$(KERNEL): $(OBJECTS) | build
	$(LD) $(LDFLAGS) -o $@ $(OBJECTS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

%.o: %.asm
	$(AS) $(ASFLAGS) -o $@ $<

build:
	mkdir -p build

iso: $(KERNEL)
	mkdir -p build/isodir/boot/grub
	cp $(KERNEL) build/isodir/boot/kernel.bin
	echo 'menuentry "JupiterOS" { multiboot /boot/kernel.bin }' > build/isodir/boot/grub/grub.cfg
	grub-mkrescue -o $(ISO) build/isodir

run: $(KERNEL)
	qemu-system-x86_64 -kernel $(KERNEL) -m 64M -nographic

run-kvm: $(KERNEL)
	qemu-system-x86_64 -kernel $(KERNEL) -m 64M -nographic -enable-kvm -cpu host

clean:
	rm -rf build $(OBJECTS)

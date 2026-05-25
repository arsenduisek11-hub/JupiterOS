CC = i686-elf-gcc
ASM = nasm
CFLAGS = -ffreestanding -nostdlib -m32 -Iinclude -Ikernel -Igui -Iapps
LDFLAGS = -T linker.ld -ffreestanding -nostdlib

OBJS = boot/bootloader.o \
       kernel/kernel.o \
       kernel/memory.o \
       kernel/keyboard.o \
       kernel/mouse.o \
       kernel/video.o \
       kernel/fs.o \
       gui/gui.o \
       gui/window.o \
       gui/cursor.o \
       gui/taskbar.o \
       gui/desktop.o \
       apps/browser.o \
       apps/editor.o

all: jupiteros.bin

boot/bootloader.o: boot/bootloader.asm
	$(ASM) -f elf32 $< -o $@

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

jupiteros.bin: $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(OBJS) jupiteros.bin

run: jupiteros.bin
	qemu-system-i386 -kernel jupiteros.bin -m 128 -usb -device usb-tablet

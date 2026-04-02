# DaedalusC Root Makefile

# Toolchain (Standard x86 Bare-Metal)
CC      = i386-elf-gcc
AS      = nasm
LD      = i386-elf-ld
QEMU    = qemu-system-i386

# Fallback to local gcc if cross-compiler not found (macOS/Homebrew)
ifeq (, $(shell which $(CC)))
    ifeq (, $(shell which x86_64-elf-gcc))
        CC = gcc -m32
        LD = ld -m elf_i386
    else
        CC = x86_64-elf-gcc -m32
        LD = x86_64-elf-ld -m elf_i386
    endif
endif

# Compilation Flags
CFLAGS  = -std=c11 -Wall -Wextra -ffreestanding -nostdlib -fno-stack-protector -fno-builtin -O2 -Ikernel_qemu -mno-sse -mno-sse2 -mno-mmx -mno-80387
LDFLAGS = -T kernel_qemu/linker.ld

# Bare-metal Objects (kernel_qemu)
Q_OBJS = kernel_qemu/boot.o \
         kernel_qemu/gdt.o \
         kernel_qemu/gdt_flush.o \
         kernel_qemu/idt.o \
         kernel_qemu/interrupts.o \
         kernel_qemu/interrupt_handlers.o \
         kernel_qemu/io.o \
         kernel_qemu/serial.o \
         kernel_qemu/main.o \
         kernel_qemu/vga.o \
         kernel_qemu/keyboard.o \
         kernel_qemu/libc.o \
         kernel_qemu/fs.o \
         kernel_qemu/shell.o \
         kernel_qemu/desktop.o

.PHONY: all clean qemu dev

all: kernel.bin

# --- QEMU Bare-Metal Build ---
kernel.bin: $(Q_OBJS)
	$(LD) $(LDFLAGS) -o $@ $^
	@echo "Built: kernel.bin (Multiboot Compliant)"

kernel_qemu/%.o: kernel_qemu/%.asm
	$(AS) -f elf32 $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
kernel_qemu/desktop.o: kernel_qemu/desktop.c
	$(CC) $(CFLAGS) -c kernel_qemu/desktop.c -o kernel_qemu/desktop.o

# Launch QEMU with the kernel image
qemu: kernel.bin
	@echo "Starting DaedalusC on QEMU..."
	@echo "--------------------------------------------------------"
	@echo "Network Environment (Virtual VM Host) mapped to localhost!"
	@echo "  COM1 (0x3F8) <--> tcp:127.0.0.1:4444"
	@echo "  COM2 (0x2F8) <--> tcp:127.0.0.1:5555"
	@echo "To connect from your laptop, run:"
	@echo "  nc localhost 4444"
	@echo "Inside DaedalusC, use: 'listen com1' or 'send com2 hi'"
	@echo "--------------------------------------------------------"
	$(QEMU) -kernel kernel.bin -m 128 \
		-serial tcp:127.0.0.1:4444,server=on,wait=off \
		-serial tcp:127.0.0.1:5555,server=on,wait=off

# --- POSIX Host Simulator Build ---
dev:
	cc -std=c11 -Wall -Wextra kernel/main.c kernel/fs.c kernel/shell.c -lpthread -o daedalus_host
	./daedalus_host

clean:
	rm -f kernel.bin $(Q_OBJS) daedalus_host

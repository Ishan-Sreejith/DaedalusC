# 🖥 IcarusK — QEMU / Bare-Metal Guide

This repository contains the bare-metal port of the IcarusK Runtime. This guide outlines how to build and boot the kernel on a simulated x86 computer.

## 📦 Dependencies

To build the kernel from source, you'll need a standard ELF toolchain. On macOS, this is easily installed via Homebrew.

### 1. Assembler (NASM)
The bootloader entry-point is written in x86 Assembly.
```bash
brew install nasm
```

### 2. Emulator (QEMU)
To run the kernel on a simulated hardware environment.
```bash
brew install qemu
```

### 3. Cross-Compiler (i386-elf-gcc) - Recommended
While the `Makefile` will attempt to use your local `gcc` with the `-m32` flag, a dedicated i386 cross-compiler is recommended for more stable ELF generation.
```bash
brew tap nativeos/i386-elf-toolchain
brew install i386-elf-binutils i386-elf-gcc
```

## 🛠 Building & Booting

### Step 1: Compile the Binary
Run the top-level `Makefile` to generate the `kernel.bin` multiboot image.
```bash
make clean
make
```

### Step 2: Boot on QEMU
To launch the emulator and see your kernel in action:
```bash
make qemu
```

This will open a QEMU window showing the IcarusK kernel booting. You should see:
- The IcarusK ASCII art banner
- Status messages showing what's initialized (GDT, IDT, Keyboard, VGA)
- A shell prompt where you can type commands

### Step 3: Interact with the Shell
Once the kernel is running, you can type commands like:
- `help` - Show available commands
- `ls` - List files in the current directory
- `cd /` - Change directory
- `pwd` - Print working directory
- `cat <file>` - Display file contents
- `mkdir <dir>` - Create a directory
- `echo <text>` - Print text

## ⚠️ Troubleshooting

### QEMU Window Doesn't Appear
- **macOS**: Make sure QEMU is installed via Homebrew: `brew install qemu`
- **Linux/WSL**: You may need to use `-display none` and capture output differently
- **Headless servers**: Use the alternative runner: Create a script with `-nographic` mode

### Architecture Mismatch
If you see errors about toolchains:
- **`ld: i386-elf-ld: no such file`**: Install the cross-toolchain:
  ```bash
  brew tap nativeos/i386-elf-toolchain
  brew install i386-elf-binutils i386-elf-gcc
  ```
- **Alternative**: The Makefile will try to use your system `gcc` with `-m32` flag as a fallback

### Stack Errors / Triple Faults
The kernel currently uses a 16KB stack defined in `boot.asm`. If you encounter crashes:
1. Edit `kernel_qemu/boot.asm`
2. Increase the stack size: change `resb 16384` to a larger value like `resb 32768`
3. Rebuild: `make clean && make`

### Keyboard Input Not Responding
The keyboard handler uses hardware interrupts (IRQ1 mapped to INT 33). If typing has no effect:
- Make sure interrupts are enabled (the code calls `sti`)
- Check that the PIC (Programmable Interrupt Controller) was properly remapped in `pic_remap()`

### Kernel Hangs at Boot
If QEMU starts but the kernel doesn't display anything:
1. Verify the multiboot header is correct in `boot.asm`
2. Check that VGA memory writes are working - try increasing verbosity
3. Ensure the GDT and IDT are properly initialized
4. The kernel may be crashing silently; look for INT 0 (divide by zero) or other exceptions

## 📝 Notes

- The kernel uses a fully in-memory filesystem (`fs.c`) with no persistent storage
- All shell commands are built into the kernel - there are no external programs
- The VGA driver only supports 80x25 text mode (standard IBM PC)
- This is a proof-of-concept bare-metal OS, not a production system

Handcrafted by Ishan.

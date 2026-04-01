# IcarusK - Bare-Metal OS Setup Guide

## ✅ What's Fixed

1. **QEMU Configuration**: Updated `make qemu` to properly launch QEMU with:
   - Proper memory allocation (256 MB)
   - CPU specification for better compatibility
   - Display window that shows VGA output
   - Multiboot kernel loading

2. **Compilation Issues**:
   - Fixed NULL definition conflict in `libc.h` (was redefining stddef.h's NULL)
   - Added explicit declaration of `fgets` in `main.c`
   - Ensured proper cross-compiler fallback chain

3. **Kernel Improvements**:
   - Added detailed boot status messages showing what's initializing
   - Improved main.c with better output and keyboard ready message
   - Verified GDT, IDT, and PIC remapping works correctly

4. **Documentation**:
   - Updated `RUN_QEMU.md` with comprehensive troubleshooting
   - Added proper build steps and expected output
   - Included keyboard and shell command examples

## 🚀 Quick Start

```bash
# Build the kernel
make clean
make

# Run on QEMU
make qemu
```

You should see a QEMU window open with the IcarusK kernel running and displaying:
```
  ____                _       _
 |  _ \  __ _  ___  __| | __ _| |_   _ ___
 | | | |/ _` |/ _ \/ _` |/ _` | | | | / __|
 | |_| | (_| |  __/ (_| | (_| | | |_| \__ \
 |____/ \__,_|\___|\___|\___|_|\___|
  IcarusK OS x86  ·  Bare-Metal (v2.2)
  ──────────────────────────────────────────

✓ Filesystem initialized
✓ Global Descriptor Table loaded
✓ Interrupt Descriptor Table loaded
✓ Keyboard controller ready
✓ VGA text mode initialized

IcarusK is ready for commands.
...
```

## 📦 System Requirements

### macOS (Recommended)
```bash
brew install nasm qemu
# Optional but recommended for better ELF support:
brew tap nativeos/i386-elf-toolchain
brew install i386-elf-binutils i386-elf-gcc
```

### Linux
```bash
sudo apt-get install nasm qemu-system-i386 build-essential
# Optional:
sudo apt-get install i386-elf-binutils i386-elf-gcc
```

## 🎮 Using the Shell

Once the kernel boots, you can interact with the shell:

```
icarusk/ $ help
Available commands:
  help       - Show this help message
  ls         - List directory contents
  cd         - Change directory
  pwd        - Print working directory
  cat        - Display file contents
  echo       - Print text
  mkdir      - Create directory
  ... (and many more)
```

## 🔧 Architecture

The bare-metal kernel consists of:

```
kernel_qemu/
├── boot.asm              # Bootloader entry point (Multiboot header)
├── gdt.c / gdt_flush.asm # Global Descriptor Table
├── idt.c / interrupts.asm # Interrupt Descriptor Table
├── io.asm                # Hardware I/O ports (inb/outb)
├── keyboard.c            # PS/2 Keyboard controller
├── vga.c                 # VGA text mode driver
├── main.c                # Kernel main entry
├── shell.c               # Command shell
├── fs.c                  # Virtual filesystem
├── libc.c / libc.h       # C standard library implementation
└── linker.ld             # ELF linker script
```

## 🐛 Troubleshooting

### QEMU window doesn't appear
- Ensure QEMU is properly installed: `which qemu-system-i386`
- Try running directly: `qemu-system-i386 -kernel kernel.bin -m 256`

### Black screen / no output
- The VGA text mode (0xB8000) should be working
- Check that the boot process completes (no triple faults)
- Verify interrupts are properly remapped in pic_remap()

### Keyboard not responding
- Make sure you click in the QEMU window to focus it
- The kernel initializes the keyboard on IRQ1 (INT 33)
- If still not working, check the keyboard handler in keyboard.c

### Build fails with "i386-elf-gcc not found"
- The Makefile automatically falls back to `x86_64-elf-gcc -m32`
- If that also fails, it uses system `gcc -m32`
- Install the proper toolchain for best results

## 📊 Build Output

A successful build should show:
```
Built: kernel.bin (Multiboot Compliant)
```

The resulting `kernel.bin` is a 32KB ELF 32-bit LSB executable that:
- Includes the Multiboot header required by QEMU's kernel loader
- Contains the GDT, IDT, and interrupt handlers compiled into the image
- Has a 16KB stack allocated in the BSS section
- Uses position-independent code where possible

## 🎯 Next Steps

1. **Add more shell commands** in `shell.c`
2. **Implement persistence** - currently filesystem is in-memory only
3. **Add more device drivers** - CMOS, disk, network
4. **Optimize performance** - consider using paging, better memory management
5. **Test on real hardware** - the kernel should work on actual x86 machines too

## ⚡ Performance Notes

- The kernel uses a simple linear memory allocator (heap.c style)
- All operations are synchronous (no async I/O)
- The shell uses a simple command parser
- VGA updates are done character-by-character

## 📝 License

Handcrafted by Ishan - Educational use only.


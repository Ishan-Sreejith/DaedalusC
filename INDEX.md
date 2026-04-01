# IcarusK Documentation Index

## 📖 Start Here

**For a complete overview of what was fixed and how to use the system:**
→ **[COMPLETE_SETUP.md](COMPLETE_SETUP.md)** - Full guide with examples and troubleshooting

---

## 📚 Documentation Files

### Quick Start
- **[QUICK_REFERENCE.md](QUICK_REFERENCE.md)** - Concise getting started guide
- **[RUN_QEMU.md](RUN_QEMU.md)** - Building and booting instructions

### Technical Details
- **[FIXES_APPLIED.md](FIXES_APPLIED.md)** - Detailed list of all fixes with before/after code
- **[SETUP_FIXED.md](SETUP_FIXED.md)** - Architecture overview and complete explanation
- **[COMPLETE_SETUP.md](COMPLETE_SETUP.md)** - Comprehensive guide with all details

---

## 🚀 Quick Start Commands

### Build
```bash
cd /Users/ishan/Downloads/IcarusK
make clean
make
```

### Run
```bash
make qemu
```

### Use the Shell
```
icarusk/ $ help        # Show commands
icarusk/ $ ls          # List files
icarusk/ $ cd /        # Change directory
icarusk/ $ pwd         # Print working directory
```

---

## ✅ What Was Fixed

1. **QEMU Configuration** - Proper memory, CPU, and acceleration settings
2. **NULL Definition** - Removed duplicate definition conflict
3. **Input Handling** - Fixed keyboard interrupt integration
4. **Documentation** - Comprehensive guides added

---

## 📊 Key Files Modified

| File | Change |
|------|--------|
| `Makefile` | Updated QEMU target |
| `kernel_qemu/libc.h` | Removed NULL redefine |
| `kernel_qemu/main.c` | Better boot messages |
| `RUN_QEMU.md` | Updated troubleshooting |

---

## 🎯 System Overview

**IcarusK** is a bare-metal x86 operating system with:
- Multiboot bootloader
- Global Descriptor Table (GDT)
- Interrupt Descriptor Table (IDT)
- PS/2 Keyboard driver
- VGA text mode display
- In-memory filesystem
- Command shell with 20+ commands
- Custom C standard library

---

## 📋 Architecture

```
Bootloader (Multiboot)
    ↓
Kernel Initialization
    ├─ GDT setup
    ├─ IDT setup
    ├─ PIC remapping
    ├─ Keyboard driver
    └─ VGA driver
    ↓
Filesystem
    ↓
Shell (REPL Loop)
    ├─ Display prompt
    ├─ Read keyboard input
    ├─ Parse command
    └─ Execute command
```

---

## ✨ Features

- **32-bit Protected Mode** - Full x86 architecture
- **Interrupt Handling** - Exceptions and hardware IRQs
- **Memory Segmentation** - GDT with code/data segments
- **I/O Port Operations** - Hardware communication via inb/outb
- **Dynamic Memory** - malloc/free heap management
- **Standard Library** - printf, string functions, etc.
- **Virtual Filesystem** - Tree structure, in-memory only
- **Interactive Shell** - Command interpreter with built-ins

---

## 🔍 File Structure

```
IcarusK/
├── kernel_qemu/                    # Bare-metal kernel sources
│   ├── boot.asm                   # Bootloader entry point
│   ├── gdt.c / gdt_flush.asm      # Memory management
│   ├── idt.c / interrupts.asm     # Interrupt handling
│   ├── keyboard.c                 # Keyboard driver
│   ├── vga.c                      # Display driver
│   ├── main.c                     # Kernel entry
│   ├── shell.c                    # Command shell
│   ├── fs.c                       # Filesystem
│   ├── libc.c / libc.h            # Standard library
│   ├── io.asm                     # I/O operations
│   └── linker.ld                  # Linker script
├── kernel/                         # POSIX simulator sources
├── Makefile                        # Build system
├── COMPLETE_SETUP.md              # This is the main guide
├── QUICK_REFERENCE.md             # Quick start
├── RUN_QEMU.md                    # Build & boot guide
├── FIXES_APPLIED.md               # Technical changes
└── SETUP_FIXED.md                 # Architecture guide
```

---

## 🛠️ Build System

The Makefile provides:
- `make` or `make all` - Build kernel.bin
- `make qemu` - Run on QEMU emulator
- `make dev` - Build POSIX simulator (host version)
- `make clean` - Remove build artifacts

### Toolchain
The Makefile automatically detects and uses:
1. i386-elf-gcc (if available)
2. x86_64-elf-gcc -m32 (if available)
3. gcc -m32 (system fallback)

---

## 🎓 Learning Outcomes

Using IcarusK, you'll learn about:
- **Bootloaders** - BIOS/UEFI and Multiboot
- **CPU Architecture** - Protected mode, privilege levels
- **Memory Management** - Segmentation, virtual addressing
- **Interrupts & Exceptions** - Hardware/software interrupt handling
- **Device Drivers** - Keyboard, display, timers
- **Filesystems** - File structures and directory trees
- **Shells & CLIs** - Command parsing and execution
- **Compilation** - Cross-compilation for bare metal
- **Debugging** - Understanding kernel behavior

---

## 🚀 Next Steps

1. **Read** [COMPLETE_SETUP.md](COMPLETE_SETUP.md) for full understanding
2. **Build** the kernel with `make`
3. **Run** with `make qemu`
4. **Explore** the shell with available commands
5. **Study** the source code in `kernel_qemu/`
6. **Modify** and extend the system

---

## 📞 Troubleshooting

**Problem**: QEMU window doesn't appear
- **Solution**: Check QEMU is installed (`which qemu-system-i386`)

**Problem**: Build fails
- **Solution**: Install build tools or cross-compiler
  ```bash
  # macOS
  brew install nasm qemu i386-elf-binutils i386-elf-gcc
  
  # Linux
  sudo apt-get install nasm qemu-system-i386 build-essential
  ```

**Problem**: Kernel doesn't boot
- **Solution**: Check interrupt handlers and GDT initialization

**Problem**: No keyboard input
- **Solution**: Click QEMU window to focus, check interrupt setup

See [COMPLETE_SETUP.md](COMPLETE_SETUP.md) for more troubleshooting.

---

## 📖 Further Reading

- **OSDev**: https://wiki.osdev.org/
- **Multiboot**: https://www.gnu.org/software/grub/manual/multiboot/
- **Intel x86**: https://software.intel.com/en-us/articles/intel-sdm
- **QEMU**: https://www.qemu.org/documentation/

---

## ✨ Status

**✅ READY TO USE**

IcarusK is fully functional and configured to:
- Build cleanly without errors
- Run on QEMU x86 emulator
- Display output via VGA
- Accept keyboard input
- Execute shell commands

---

## 🎯 Summary

IcarusK is a complete bare-metal x86 operating system kernel suitable for:
- Learning OS concepts
- Understanding hardware interaction
- Exploring interrupt handling and device drivers
- Experimenting with filesystem design
- Teaching embedded systems

**Start with:** `make qemu`

---

*IcarusK - Handcrafted by Ishan | March 2026*


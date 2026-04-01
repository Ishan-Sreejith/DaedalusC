# DaedalusC 🚀

Welcome to **DaedalusC**! This is a handcrafted, bare-metal x86 operating system kernel built from scratch. It's a passion project designed to explore low-level hardware interactions, memory management, and crafting a custom shell environment—no fancy modern OS bloat, just you, the CPU, and the hardware.

## What is this? 🤔

DaedalusC is entirely self-contained. It features:
- A custom bootloader (Multiboot compliant)
- Its own Global Descriptor Table (GDT) and Interrupt Descriptor Table (IDT)
- Hardware-level drivers for VGA text mode and PS/2 keyboards
- A fully in-memory virtual filesystem
- An interactive, integrated shell with built-in commands (like `ls`, `cd`, `read`, `write`, and even a tiny text editor!)
- A network testing environment over emulated serial ports!

It's essentially an entire micro-operating system that you can compile and boot instantly.

## 🛠️ Getting Started

First, make sure you have the basics installed. You'll need `make`, `nasm`, a C compiler, and `qemu` to run the emulation.
For macOS, just grab them via Homebrew:
```bash
brew install nasm qemu
```

### Try it out!

Building and running the OS right inside QEMU is super easy:
```bash
make clean && make
make qemu
```
You'll see a wild screen pop up with the DaedalusC splash art. Type `help` to see what commands you can play with!

*(Pro-tip: If you want to test the POSIX-compatible parts of the shell directly on your host machine without booting the full kernel, just run `make dev`)*

## 📂 Project Structure

- `kernel_qemu/` - This is where the magic happens! It contains the bare-metal hardware drivers (VGA, Keyboard, Serial), the bootloader, memory segmentation, and the actual kernel entry-point.
- `kernel/` - A posix-compliant simulator version of the shell logic.

## 💡 Why?

Because operating systems are fascinating. Getting comfortable with exactly how interrupts get routed, how the CPU pushes values to the stack before jumping into a C handler, or how a single keystroke makes its way to a command prompt—it teaches you more about computers than any high-level framework ever could.

I hope you have as much fun exploring it as I did building it! If you find any cool quirks or want to add a new command, feel free to dive into the code.

Happy hacking!
— *Ishan*

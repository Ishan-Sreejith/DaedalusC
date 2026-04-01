#!/bin/bash
# IcarusK QEMU Runner

# Check if kernel.bin exists
if [ ! -f kernel.bin ]; then
    echo "Error: kernel.bin not found. Run 'make' first."
    exit 1
fi

# Check if QEMU is installed
if ! command -v qemu-system-i386 &> /dev/null; then
    echo "Error: qemu-system-i386 not found. Install QEMU first."
    exit 1
fi

echo "Starting IcarusK in QEMU..."
echo "Press Ctrl+A then X to quit QEMU."
echo ""

# Run QEMU with the kernel
# Using -kernel with Multiboot format should work
qemu-system-i386 \
    -kernel kernel.bin \
    -m 256 \
    -nographic \
    -serial stdio \
    -monitor none \
    -no-reboot

echo ""
echo "QEMU session ended."


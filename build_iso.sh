#!/bin/bash
# IcarusK ISO Builder - Creates a bootable GRUB ISO

set -e

cd "$(dirname "$0")"

echo "Building bootable IcarusK ISO..."

# Check dependencies
if ! command -v grub-mkrescue &> /dev/null; then
    echo "Error: grub-mkrescue not found."
    echo "Install it with: brew install grub xorriso"
    exit 1
fi

# Create temporary ISO directory structure
ISODIR="/tmp/icarusk_iso"
rm -rf "$ISODIR"
mkdir -p "$ISODIR/boot/grub"

# Copy kernel
cp kernel.bin "$ISODIR/boot/"

# Create GRUB config
cat > "$ISODIR/boot/grub/grub.cfg" << 'EOF'
set timeout=10
set default=0

menuentry "IcarusK OS" {
    multiboot /boot/kernel.bin
    boot
}
EOF

# Build ISO
echo "Creating ISO image..."
grub-mkrescue -o icarusk.iso "$ISODIR" 2>/dev/null || {
    echo "Warning: grub-mkrescue failed, trying alternative method..."
    # Try with different parameters if the first attempt fails
    grub-mkrescue -o icarusk.iso "$ISODIR"
}

rm -rf "$ISODIR"
echo "✓ Created: icarusk.iso"
echo ""
echo "To boot the ISO, run:"
echo "  qemu-system-i386 -m 256 -cdrom icarusk.iso"


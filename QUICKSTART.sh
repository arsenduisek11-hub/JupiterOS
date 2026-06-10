#!/bin/bash

echo "================================================"
echo "  JupiterOS v2.0 - Quick Start Guide"
echo "================================================"
echo ""

if ! command -v x86_64-elf-gcc &> /dev/null; then
    echo "[!] ERROR: x86_64-elf-gcc not found"
    echo ""
    echo "Install cross-compiler:"
    echo "  Ubuntu/Debian: sudo apt-get install gcc-x86-64-linux-gnu binutils-x86-64-linux-gnu"
    echo "  Fedora: sudo dnf install gcc-x86_64-elf"
    echo ""
    exit 1
fi

if ! command -v nasm &> /dev/null; then
    echo "[!] ERROR: nasm not found"
    echo ""
    echo "Install NASM assembler:"
    echo "  Ubuntu/Debian: sudo apt-get install nasm"
    echo "  Fedora: sudo dnf install nasm"
    echo ""
    exit 1
fi

if ! command -v qemu-system-x86_64 &> /dev/null; then
    echo "[!] ERROR: QEMU not found"
    echo ""
    echo "Install QEMU:"
    echo "  Ubuntu/Debian: sudo apt-get install qemu-system-x86"
    echo "  Fedora: sudo dnf install qemu-system-x86"
    echo ""
    exit 1
fi

echo "[✓] All dependencies found"
echo ""
echo "Building JupiterOS v2.0..."
echo ""

make clean > /dev/null 2>&1
make all

echo ""
echo "================================================"
echo "  Build Complete!"
echo "================================================"
echo ""
echo "Next steps:"
echo "  make run              - Run in QEMU"
echo "  make run-kvm          - Run with KVM (faster)"
echo "  make run-vesa         - Run with graphics"
echo "  make iso              - Create bootable ISO"
echo ""

nasm src/bootloader/boot_sect.asm -f bin -o build/boot_sect.bin
qemu-system-i386 -fda build/boot_sect.bin
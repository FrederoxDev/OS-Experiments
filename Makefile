GCC=toolchain/i386-elf/bin/i386-elf-gcc
LD=toolchain/i386-elf/i386-elf/bin/ld
NASM=nasm

BUILD=_build

run: build
	qemu-system-i386 -fda $(BUILD)/os-image

build: kernel boot_sect
	cat $(BUILD)/boot_sect.bin $(BUILD)/kernel.bin > $(BUILD)/os-image

kernel: kernel/kernel_entry.asm kernel/kernel.c
	$(GCC) -ffreestanding -c kernel/kernel.c -o $(BUILD)/kernel.o
	$(NASM) kernel/kernel_entry.asm -f elf -o $(BUILD)/kernel_entry.o
	$(LD) -o $(BUILD)/kernel.bin -Ttext 0x1000 $(BUILD)/kernel_entry.o $(BUILD)/kernel.o --oformat binary

boot_sect: $(wildcard boot/*.asm)
	$(NASM) boot/boot_sect.asm -f bin -o $(BUILD)/boot_sect.bin
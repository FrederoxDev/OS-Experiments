GCC=toolchain/i386-elf/bin/i386-elf-gcc
LD=toolchain/i386-elf/i386-elf/bin/ld
NASM=nasm

# Directories
BUILD=_build
SRC := ./kernel

# Source directories
DIRS := $(shell find $(SRC) -type d)

# Source files
ASM_SOURCES := $(foreach dir,$(DIRS),$(wildcard $(dir)/*.asm))
C_SOURCES := $(foreach dir,$(DIRS),$(wildcard $(dir)/*.c))
HEADERS := $(wildcard $(SRC)/**/*.h)

# Object files
ASM_OBJECTS := $(patsubst $(SRC)/%.asm,$(BUILD)/%.o,$(ASM_SOURCES))
C_OBJECTS := $(patsubst $(SRC)/%.c,$(BUILD)/%.o,$(C_SOURCES))

# Flags
CFLAGS := -ffreestanding

run: build
	qemu-system-i386 -drive format=raw,file=$(BUILD)/os-image,if=floppy

build: kernel boot_sect
	cat $(BUILD)/boot_sect.bin $(BUILD)/kernel.bin > $(BUILD)/os-image

#
#	KERNEL
#
kernel: $(ASM_OBJECTS) $(C_OBJECTS)
	$(LD) -Ttext 0x1000 --oformat binary -o $(BUILD)/kernel.bin $(ASM_OBJECTS) $(C_OBJECTS)

# *.asm
$(BUILD)/%.o: $(SRC)/%.asm
	$(NASM) $< -f elf -o $@

# *.c
$(BUILD)/%.o: $(SRC)/%.c $(HEADERS)
	$(GCC) $(CFLAGS) -c $< -o $@


#
#	BOOTLOADER
#
boot_sect: $(wildcard boot/*.asm)
	$(NASM) boot/boot_sect.asm -f bin -o $(BUILD)/boot_sect.bin

#
# 	CLEAN
#
clean:
	rm -rf $(BUILD)/*.o $(BUILD)/kernel.bin
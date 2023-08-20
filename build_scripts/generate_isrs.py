p = 0
isrs_with_error_codes = [8, 10, 11, 12, 13, 14, 17, 21, 29, 30, 0]
asm_text = """
; THIS FILE IS AUTO-GENERATED BY build_scripts/generate_isrs.py

[bits 32]
extern i386_ISR_Handler

isr_common:
    pusha   ; save current state

    xor eax, eax ; eax = 0
    mov ax, ds
    push eax

    mov ax, 0x10    ; use kernel data segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    push esp    ; pass pointer to the stack to C
    call i386_ISR_Handler
    add esp, 4

    pop eax         ; restore old segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    popa
    add esp, 8      ; remove error code and interrupt number
    iret   

%macro ISR_NOERRORCODE 1

global i386_ISR%1:
i386_ISR%1:
    push 0
    push %1
    jmp isr_common

%endmacro

%macro ISR_ERRORCODE 1

global i386_ISR%1:
i386_ISR%1:
    push %1
    jmp isr_common

%endmacro

; Begin ISRS
"""

c_text = """
// THIS FILE IS AUTO-GENERATED BY build_scripts/generate_isrs.py

#include "isr_gen.h"
#include "idt.h"
#include "gdt.h"

"""

for i in range(0, 256):
    c_text += f"void __attribute__((cdecl)) i386_ISR{i}();\n"

c_text += """
void i386_ISR_InitializeGates() 
{
"""

for i in range(0, 256):
    c_text += f"    i386_IDT_SetGate({i}, i386_ISR{i}, i386_GDT_CODE_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);\n"

    if i == isrs_with_error_codes[p]:
        asm_text += f"ISR_ERRORCODE {i}\n"
        p = p + 1
        continue

    asm_text += f"ISR_NOERRORCODE {i}\n"

c_text += "}"

with open("./kernel/i386/isr_generated.asm", "w") as file:
    file.write(asm_text)

with open("./kernel/i386/isr_gen.c", "w") as file:
    file.write(c_text)
[ org 0x7c00 ]
[ bits 16 ]

; initialise stack
mov bp, 0x9000              
mov sp, bp

mov bx, MSG_REAL_MODE
call print_string

call switch_to_pm ; Never Returns
jmp $

; includes
%include "src/print_string.asm"
%include "src/gdt.asm"
%include "src/switch_to_pm.asm"
%include "src/pm_print_string.asm"

[bits 32]
BEGIN_PM:
    mov ebx, MSG_PROT_MODE
    call print_string_pm

    jmp $

; Global variables
MSG_REAL_MODE db "Started in 16 - bit Real Mode", 0
MSG_PROT_MODE db "Successfully landed in 32 - bit Protected Mode", 0


; Padding and magic BIOS number
times 510-($-$$) db 0
dw 0xaa55
[ org 0x7c00 ]
[ bits 16 ]
KERNEL_OFFSET equ 0x1000

mov [BOOT_DRIVE], dl

; initialise stack
mov bp, 0x9000              
mov sp, bp

mov bx, MSG_REAL_MODE
call print_string

call load_kernel

call switch_to_pm ; Never Returns
jmp $

; includes
%include "boot/print_string.asm"
%include "boot/gdt.asm"
%include "boot/switch_to_pm.asm"
%include "boot/pm_print_string.asm"
%include "boot/disk_load.asm"

[bits 16]
load_kernel:
    mov bx, MSG_LOAD_KERNEL
    call print_string

    mov bx, KERNEL_OFFSET       
    mov dh, 15                  
    mov dl, [ BOOT_DRIVE ]     
    call disk_load         

    ret 

[bits 32]
BEGIN_PM:
    mov ebx, MSG_PROT_MODE
    call print_string_pm

    call KERNEL_OFFSET ; jump to the kernel
    jmp $

; Global variables
BOOT_DRIVE db 0
MSG_REAL_MODE db "Started in 16 - bit Real Mode", ENDL, 0
MSG_PROT_MODE db "Entered 32 - bit Protected Mode", 0
MSG_LOAD_KERNEL db "Loading Kernel into memory.", ENDL, 0


; Padding and magic BIOS number
times 510-($-$$) db 0
dw 0xaa55
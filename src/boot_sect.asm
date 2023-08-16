[ org 0x7c00 ]

mov [BOOT_DRIVE], dl        ; BIOS stores our boot drive in DL

; initialise stack
mov bp, 0x8000              
mov sp, bp

mov bx, 0x9000              ; Load 5 sectors to 0x0000 (ES ):0x9000 (BX)
mov dh, 5   
mov dl, [BOOT_DRIVE]
call disk_load

mov dx, [0x9000]
call print_hex

mov dx, [0x9000 + 512]
call print_hex

; [bits 16]
;     switch_to_pm:
;     cli
;     lgdt [gdt_descriptor]

;     mov eax, cr0            ; To make the switch to protected mode , we set
;     or eax, 0x1             ; the first bit of CR0 , a control register
;     mov cr0, eax            ; Update the control register

;     jmp CODE_SEG:init_pm    ; Make a far jump ( i.e. to a new segment ) to our 32 - bit
;                             ; code. This also forces the CPU to flush its cache of
;                             ; pre - fetched and real - mode decoded instructions , which can
;                             ; cause problems.


jmp $


; includes
%include "src/print_string.asm"
%include "src/print_hex.asm"
%include "src/disk_load.asm"
%include "src/gdt.asm"

; globals
BOOT_DRIVE: db 0

; Padding and magic BIOS number
times 510-($-$$) db 0
dw 0xaa55

; We know that BIOS will load only the first 512 - byte sector from the disk ,
; so if we purposely add a few more sectors to our code by repeating some
; familiar numbers , we can prove to ourselfs that we actually loaded those
; additional two sectors from the disk we booted from.
times 256 dw 0xdada
times 256 dw 0xface
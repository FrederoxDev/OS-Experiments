; GDT
gdt_start:

; Null Descriptor
gdt_null:       
    dd 0x0
    dd 0x0

; Code Segment Descriptor
gdt_code:
    ; base=0x0, limit=0xfffff
    ; 1st flags : (present)1 (privilege)00 (descriptor type)1 -> 1001 b
    ; type flags : (code)1 (conforming)0 (readable )1 ( ccessed)0 -> 1010 b
    ; 2nd flags : (granularity)1 (32 - bit default)1 (64 - bit seg)0 (AVL)0 -> 1100 b
    dw 0xffff ; Limit (bits 0 - 15)
    dw 0x0 ; Base (bits 0 - 15)
    db 0x0 ; Base (bits 16 - 23)
    db 10011010b ; 1st flags, type flags
    db 11001111b ; 2nd flags, Limit (bits 16 - 19)
    db 0x0 ; Base (bits 24 -3 1)

; Data Segment Descriptor
gdt_data:
    ; Same as code segment except for the type flags
    ; type flags : (code)0 (expand down)0 (writable)1 (accessed)0 -> 0010b
    dw 0xffff ; Limit ( bits 0 -15)
    dw 0x0 ; Base ( bits 0 -15)
    db 0x0 ; Base ( bits 16 -23)
    db 10010010b ; 1st flags , type flags
    db 11001111b ; 2nd flags , Limit ( bits 16 -19)
    db 0x0 ; Base ( bits 24 -31)

; Start and end used to calculate the size via assembler
gdt_end: 

; GDT Descriptor
gdt_descriptor:
    dw gdt_end - gdt_start - 1          ; Size of GDT
    dd gdt_start                        ; Start address


CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start

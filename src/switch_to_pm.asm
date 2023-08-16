[bits 16]
switch_to_pm:
    cli
    lgdt [gdt_descriptor]

    mov eax, cr0            ; To make the switch to protected mode , we set
    or eax, 0x1             ; the first bit of CR0 , a control register
    mov cr0, eax            ; Update the control register

    jmp CODE_SEG:init_pm    ; Make a far jump ( i.e. to a new segment ) to our 32 - bit
                            ; code. This also forces the CPU to flush its cache of
                            ; pre - fetched and real - mode decoded instructions , which can
                            ; cause problems.


[bits 32]
; Initialise registers and stack in one place
init_pm:
    mov ax, DATA_SEG
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    ; Update stack
    mov ebp, 0x90000
    mov esp, ebp
    call BEGIN_PM
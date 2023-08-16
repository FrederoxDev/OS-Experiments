disk_load:
    push dx             ; dx = number of sectors to read
    mov ah, 0x02        ; BIOS read sector function
    mov al, dh          ; read DH cylinders
    mov ch, 0x00        ; select cylinder 0
    mov dh, 0x00        ; select head 0
    mov cl, 0x02        ; start reading from the second sector

    int 0x13
    
    jc disk_error       ; Jump if error (Carry flag set)

    pop dx              
    cmp dh, al          ; if AL ( sectors read ) != DH ( sectors expected )
    jne disk_error      ; display error
    ret


disk_error:
    mov bx, DISK_ERROR_MSG
    call print_string
    jmp $

DISK_ERROR_MSG db 'Disk read error!', ENDL, 0
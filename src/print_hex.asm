;
; Prints a 16 bit hexadecimal number
; Parameters
;   dx: number
;
print_hex:
    pusha
    mov ah, 0x0e
    
    mov cx, 4 ; set the loop counter to 4

print_nibble:
    ; Extract the lowest 4 bits to keep only the lowest 4
    mov al, dl  
    and al, 0x0F    ; Mask the higher bits

    ; Convert to a hexidecimal digit
    add al, '0'
    cmp al, '9'
    jbe add_to_buffer   ; Check if it in the range '0' to '9'
    add al, 7           ; Else Adjust to letters 'A-F'

    ; Add the digit to the buffer
    add_to_buffer:
    lea di, [HEX_OUT]
    add di, 1           ; Skips the '0x' characters at the start
    add di, cx          ; cx decreases for each iteration, starts at 4
    mov [di], al        ; '0x0000'[di] = al

    ; Shift dx to the right by 4 bits 
    shr dx, 4
    loop print_nibble

    mov bx, HEX_OUT
    call print_string

    popa
    ret

HEX_OUT:
    db '0x0000', ENDL, 0
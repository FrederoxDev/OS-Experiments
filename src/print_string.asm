;
; Prints a string
; Parameters:
;   bx: string to print
;
print_string:
    pusha
    mov ah, 0x0e
    mov al, [bx]
    int 0x10

next_character:
    inc bx
    mov al, [bx]

    ; Check for null-terminator
    cmp al, 0x00
    je end_print_string

    ; Print character and move to next
    int 0x10
    jmp next_character
    
end_print_string:
    popa
    ret

%define ENDL 0x0D, 0x0A
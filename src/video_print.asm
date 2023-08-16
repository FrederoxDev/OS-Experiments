[bits 32]

; Constants
VIDEO_MEMORY equ 0xb8000
WHITE_ON_BLACK equ 0x0f

;
; prints a null-terminated string
; Parameters:
;   edx: string
; 
print_string_pm:
    pusha
    mov edx, VIDEO_MEMORY

print_string_pm_loop:
    mov al, [ebx]               ; Character
    mov ah, WHITE_ON_BLACK      ; Character attributes (font color, background, blinking etc..)

    cmp al, 0                   ; null terminating character
    je print_string_pm_done

    mov [edx], ax               ; Store char and attributes at current cell
    add ebx, 1                  ; Move to the next character in the string
    add edx, 2                  ; Move to the next character cell in video memory

    jmp print_string_pm_done


print_string_pm_done
    popa
    ret
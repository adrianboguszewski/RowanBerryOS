; print string in real mode
; address of string passed with stack
print_string:
    push bp
    mov bp, sp
    push ax
    push bx
    mov bx, [bp + 4]
    mov ah, 0x0e    ; int=0x10/ah=0x0e -> BIOS tele-type output
    
lp:
    mov al, [bx]    ; character to al
    cmp al, 0       
    je exit
    int 0x10        ; print
    inc bx
    jmp lp
    
exit:
    pop bx
    pop ax
    pop bp
    ret

; print hex number in real mode
; value passed with stack
print_hex:
    push bp
    mov bp, sp
    push ax
    push bx
    push cx
    push dx
    push di
    mov dx, [bp + 4]
    xor cx, cx
    mov cx, 5

start:
    mov ax, dx
    shr dx, 4           ; next hexdecimal character
    and ax, 0x000f      
    cmp al, 10
    jge greater
    add al, '0'
    jmp next
    
greater:
    add al, 'a' - 10
    
next:
    mov di, HEX_OUT
    add di, cx          ; compute address of character
    mov [di], al
    dec cx
    cmp cx, 1
    jg start
    
    mov bx, HEX_OUT
    push bx
    call print_string
    add sp, 2
    pop di
    pop dx
    pop cx
    pop bx
    pop ax
    pop bp
    ret
    
HEX_OUT: db '0x0000', 0

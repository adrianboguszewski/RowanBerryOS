; print hex number in real mode
; address of word passed with dx
print_hex:
	push ax
	push bx
	push cx
	push dx
	push di
	xor cx, cx
	mov cx, 5
	
start:
	mov ax, dx
	shr dx, 4			; next hexdecimal character
	and ax, 0x000f		
	cmp al, 10
	jge greater
	add al, '0'
	jmp next
	
greater:
	add al, 'a' - 10
	
next:
	mov di, HEX_OUT
	add di, cx			; compute address of character
	mov [di], al
	dec cx
	cmp cx, 1
	jg start
	
	mov bx, HEX_OUT
	call print_string
	pop di
	pop dx
	pop cx
	pop bx
	pop ax
	ret
	
HEX_OUT: db '0x0000', 0

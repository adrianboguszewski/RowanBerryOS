; print string in real mode
; address of string passed with bx
print_string:
	push ax
	push bx
	mov ah, 0x0e	; int=0x10/ah=0x0e -> BIOS tele-type output
	
lp:
	mov al, [bx]	; character to al
	cmp al, 0		
	je exit
	int 0x10		; print
	inc bx
	jmp lp
	
exit:
	pop bx
	pop ax
	ret

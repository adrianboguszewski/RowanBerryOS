[bits 32]					; translate as 32-bit instructions

VIDEO_MEMORY equ 0xb8000
WHITE_ON_RED equ 0x4f

; print string in protected mode
; address of string passed with ebx
print_string_pm:
	push eax
	push ebx
	push edx
	mov edx, VIDEO_MEMORY
	
loop:
	mov al, [ebx]
	mov ah, WHITE_ON_RED
	
	cmp al, 0
	je done
	
	mov [edx], ax
	
	inc ebx
	add edx, 2
	
	jmp loop
	
done:
	pop edx
	pop ebx
	pop eax
	ret

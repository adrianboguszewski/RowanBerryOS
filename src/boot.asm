[org 0x7c00]

	mov bp, 0x9000				; set the stack
	mov sp, bp

	mov bx, MSG_REAL_MODE		; temporary for debugging
	call print_string

	call switch_to_pm
	
%include "print_string.asm"
%include "gdt.asm"
%include "print_string_pm.asm"
%include "switch_to_pm.asm"

[bits 32]						; next instructions translate as 32-bit

begin_pm:
	mov ebx, MSG_PROTECTED_MODE	; temporary for debugging
	call print_string_pm	

	jmp $
	
MSG_REAL_MODE 		db "Started in 16-bit Real Mode", 0
MSG_PROTECTED_MODE 	db "Successfully landed in 32-bit Protected Mode", 0

	times 510 - ($ - $$) db 0
	dw 0xaa55

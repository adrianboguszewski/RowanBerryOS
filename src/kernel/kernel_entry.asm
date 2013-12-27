[bits 32]
[extern main]
	call main	; invoke main from kernel.c
	jmp $

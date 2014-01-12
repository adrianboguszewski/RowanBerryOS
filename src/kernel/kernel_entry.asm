[bits 32]
global _start
_start:
[extern main]
    call main   ; invoke main from kernel.c
    jmp $

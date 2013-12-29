gdt_start:

gdt_null:           ; the mandatory null descriptor
    dd 0x0
    dd 0x0
    
gdt_code:           ; the code segment descriptor
    ; base =0 x0 , limit =0 xfffff ,
    ; 1 st flags : ( present )1 ( privilege )00 ( descriptor type )1 -> 1001 b
    ; type flags : ( code )1 ( conforming )0 ( readable )1 ( accessed )0 -> 1010 b
    ; 2 nd flags : ( granularity )1 (32 - bit default )1 (64 - bit seg )0 ( AVL )0 -> 1100 b
    dw 0xffff       ; limit ( bits 0 -15)
    dw 0x0          ; base (bits 0 - 15)
    db 0x0          ; base (bits 16 - 31)
    db 10011010b    ; 1st flags, type flags
    db 11001111b    ; 2nd flags, limit (bits 16 - 19)
    db 0x0          ; base (bits 24 - 31)
    
gdt_data:           ; the data segment descriptor
    ; Same as code segment except for the type flags :
    ; type flags : ( code )0 ( expand down )0 ( writable )1 ( accessed )0 -> 0010 b
    dw 0xffff       ; limit ( bits 0 -15)
    dw 0x0          ; base (bits 0 - 15)
    db 0x0          ; base (bits 16 - 31)
    db 10010010b    ; 1st flags, type flags
    db 11001111b    ; 2nd flags, limit (bits 16 - 19)
    db 0x0          ; base (bits 24 - 31)
    
gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1  ; size of our GDT , always less one of the true size
    dd gdt_start
    
    
CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start

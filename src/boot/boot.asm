[org 0x7c00]

KERNEL_OFFSET equ 0x1000        ; address to which we will load kernel

    mov [BOOT_DRIVE], dl        ; remember boot drive
    
    mov bp, 0x9000              ; set the stack
    mov sp, bp

    call load_kernel            ; load kernel

    call switch_to_pm           ; switch to protected mode
   
%include "boot/print_string.asm"
%include "boot/disk_load.asm"
%include "boot/gdt.asm"
%include "boot/switch_to_pm.asm"

[bits 16]
load_kernel: 
    mov dh, 30                  ; load first 30 sectors
    mov dl, [BOOT_DRIVE]
    push dx
    push word KERNEL_OFFSET
    call disk_load              ; load disk sectors
    add sp, 4
    ret

[bits 32]                       ; next instructions translate as 32-bit
begin_pm:    
    call KERNEL_OFFSET
    jmp $
    
CR equ 0x0d
LF equ 0x0a

BOOT_DRIVE          db 0
MSG_REAL_MODE       db "Started in 16-bit Real Mode", LF, CR, 0
MSG_PROTECTED_MODE  db "Successfully landed in 32-bit Protected Mode", 0
MSG_LOAD_KERNEL     db "Loading kernel into memory", LF, CR, 0

    times 510 - ($ - $$) db 0
    dw 0xaa55

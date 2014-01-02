[bits 16]
; switch to protected mode
switch_to_pm:
    cli                     ; disable interrupts
    lgdt [gdt_descriptor]   ; load gdt
    
    mov eax, cr0            ; make switch to protected mode
    or eax, 0x1
    mov cr0, eax

    jmp CODE_SEG:init_pm
    
[bits 32]
; initialize registers and stack
init_pm:
    mov ax, DATA_SEG
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    
    mov ebp, 0x90000
    mov esp, ebp
    
    call begin_pm

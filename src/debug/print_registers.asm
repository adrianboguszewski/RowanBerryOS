[bits 32]
global print_registers
extern dword_to_hex
extern print

print_registers:
    pushad                      ; push all registers on stack
    pushf                       ; push flags
    push ebp
    mov ebp, esp
    mov ebx, 9
    mov esi, dword REGS

loop:
    push esi
    call print
    add esp, 4
    push dword HEX
    mov eax, [ebp + 4 * ebx]
    push eax
    call dword_to_hex
    add esp, 4
    call print
    add esp, 4
    add esi, 6
    dec ebx
    jg loop
    
    pop ebp
    add esp, 36    
    ret

HEX    db '0x00000000', 10, 0
REGS db 'eax: ', 0, 'ecx: ', 0, 'edx: ', 0, 'ebx: ', 0, 'esp: ', 0, 'ebp: ', 0, 'esi: ', 0, 'edi: ', 0, 'eflags: ', 0

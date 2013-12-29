; load sectors from disk
disk_load:
    push dx
    mov ah, 0x02    ; read sector function
    mov al, dh      ; read dh sectors
    mov ch, 0x00    ; select cylinder 0
    mov dh, 0x00    ; select head 0
    mov cl, 0x02    ; select start sector
    
    int 0x13        
    
    jc disk_error   ; bios set carry flag if error occured
    
    pop dx 
    cmp dh, al 
    jne disk_error  ; if sectors read not equals sectors expected
    ret
    
disk_error:
    mov bx, MSG_DISK_ERROR
    call print_string
    
    jmp $

MSG_DISK_ERROR db "Disk read error!", 0

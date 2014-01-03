; load sectors from disk
; first parameter is memory address
; second parameter is number of sectors to read
disk_load:
    push bp
    mov bp, sp
    push bx
    push si
    mov bx, [bp + 4]
    mov dx, [bp + 6]
    mov si, dx
    mov ah, 0x02    ; read sector function
    mov al, dh      ; read dh sectors
    mov ch, 0x00    ; select cylinder 0
    mov dh, 0x00    ; select head 0
    mov cl, 0x02    ; select start sector
    
    int 0x13        
    
    jc disk_error   ; bios set carry flag if error occured

    mov dx, si
    cmp dh, al 
    jne disk_error  ; if sectors read not equals sectors expected
    pop si
    pop bx 
    pop bp
    ret
    
disk_error:
    mov bx, MSG_DISK_ERROR
    push bx
    call print_string
    add sp, 2
    
    jmp $

MSG_DISK_ERROR db "Disk read error!", 0

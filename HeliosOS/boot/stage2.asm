[BITS 16]
[ORG 0]

extern enable_a20
extern load_gdt

KERNEL_SEG equ 0x2000

start_stage2:

    call enable_a20

    call load_gdt

    mov ah,0x02
    mov al,32
    mov ch,0
    mov cl,10
    mov dh,0

    mov bx,0
    mov ax,KERNEL_SEG
    mov es,ax

    int 0x13

    jc $

    cli

    mov eax,cr0
    or eax,1
    mov cr0,eax

    jmp 0x08:protected_mode

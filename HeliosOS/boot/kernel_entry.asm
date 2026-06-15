[BITS 32]

extern kernel_main

global _start

section .bss
align 16

stack_bottom:
    resb 32768        ; 32 KB stack
stack_top:

section .text
align 4

_start:

    ; =========================
    ; STACK SETUP
    ; =========================
    mov esp, stack_top
    mov ebp, esp

    ; =========================
    ; SAFE CPU STATE
    ; =========================
    cld
    cli

    ; =========================
    ; CALL KERNEL
    ; =========================
    call kernel_main

; =========================
; FAILSAFE LOOP
; =========================
.hang:
    hlt
    jmp .hang

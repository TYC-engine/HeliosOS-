[BITS 32]

global isr0
global irq0
global irq1

extern isr_handler
extern irq_handler

isr0:
    push dword 0
    push dword 0
    jmp isr_common

irq0:
    push dword 0
    push dword 32
    jmp irq_common

irq1:
    push dword 0
    push dword 33
    jmp irq_common

isr_common:

    pusha

    call isr_handler

    popa

    add esp,8

    iretd

irq_common:

    pusha

    call irq_handler

    popa

    add esp,8

    iretd

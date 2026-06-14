global irq12

extern mouse_irq_handler

irq12:
    pusha

    in al, 0x60
    push eax
    call mouse_irq_handler
    add esp, 4

    mov al, 0x20
    out 0x20, al
    out 0xA0, al

    popa
    iretd

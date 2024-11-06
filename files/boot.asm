section .text
global _start
extern kernel_main

_start:
    mov esp, 0x9F00
    call kernel_main
    ;jmp $

times 510 - ($-$$) db 0
dw 0xaa55
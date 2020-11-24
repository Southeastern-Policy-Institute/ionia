; IRQ.ASM - Interrupt Request Wrappers
; Southeastern Policy Institute, 2020

[BITS 32]

; Imported Symbols
extern  irq_handler

; Macro for generating the stub entry-points
%macro  __irq   1

global  irq%1
irq%1:  cli
        push    byte 0
        push    byte 32+i
        jmp     irq_common_stub

%endmacro

section .text

; This generates the stub entry-points
%assign i       0
%rep    16
__irq   i
%assign i       i+1
%endrep

irq_common_stub:
        pusha
        push    ds
        push    es
        push    fs
        push    gs
        mov     ax, 0x10                ; kernel data desc
        mov     ds, ax
        mov     es, ax
        mov     fs, ax
        mov     gs, ax
        mov     eax, esp
        push    eax
        mov     eax, irq_handler
        call    eax
        pop     eax
        pop     gs
        pop     fs
        pop     es
        pop     ds
        popa
        add     esp, 8
        sti
        iret

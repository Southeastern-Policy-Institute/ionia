; ISR.ASM - Interrupt Service Routine Wrappers
; Southeastern Policy Institute, 2020

[BITS 32]

; Imported Symbols
extern  exception

; Macro for generating the stub entry-points
%macro  __isr   1

global  isr%1
isr%1:  cli
        push    byte 0
        push    byte i
        jmp     isr_common_stub

%endmacro

section .text

; This generates the stub entry-points
%assign i       0
%rep    32
__isr   i
%assign i       i+1
%endrep

; This is the wrapper itself
isr_common_stub:
        pusha
        push    ds
        push    es
        push    fs
        push    gs
        mov     ax, 0x10                ; kernel data seg
        mov     ds, ax
        mov     es, ax
        mov     fs, ax
        mov     gs, ax
        mov     eax, esp
        push    eax
        mov     eax, exception
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

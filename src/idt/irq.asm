; IRQ.ASM - Interrupt Request Wrappers
; Southeastern Policy Institute, 2020

[BITS 32]

; Exported symbols
global  install_irq

; Macro for generating the stub entry-points
%macro  __irq   1

global  irq%1
irq%1:  cli
        push    byte 0
        push    byte 32+i
        jmp     irq_common_stub

%endmacro

section .data

; IRQ Table
irq_routines:
        times   16 dd 0

section .text

; This function will install a new IRQ function pointer into the table
; Make sure to declare as:
;   extern "C" __attribute__ ((regparm(2)))
;   void install_irq (unsigned int, handler_t);
install_irq:
        cmp     eax, 15
        ja      .done
        mov     dword [irq_routines+eax*4], edx
.done:
        ret

; This function checks the IRQ table and calls a function pointer if present
irq_handler:
        push    ebp
        mov     ebp, esp
        push    ebx
        push    eax
        mov     ebx, dword [ebp+8]
        mov     eax, dword [ebx+48]
        sub     eax, 32
        mov     eax, dword [irq_routines+eax*4]
        test    eax, eax
        je      .no_func
        sub     esp, 12
        push    ebx
        call    eax
        add     esp, 16
.no_func:
        cmp     dword [ebx+48], 39
        jbe     .no_slave
        mov     al, 32
        mov     edx, 160
        out     dx, al
.no_slave:
        mov     al, 32
        mov     edx, 32
        out     dx, al
        mov     ebx, dword [ebp-4]
        leave
        ret

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

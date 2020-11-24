; Protected Mode Boot Stub
; Southeastern Policy Institute, 2020

[BITS 16]

; Imported Symbols
extern  __sector_count
extern  __sector_start
extern  __map_ent
extern  __smap
extern  k_main
extern  _init
extern  _fini

; Exported Symbols
global  __drive

; Initialized Data
section .data
; Very basic GDT setup.  All memory is available for access, and none of it
; is protected.  The data segment is prevented from execution, but not writing.
gdt:
.null   dq      0
.code   dw      0xFFFF
        dw      0
        db      0
        db      0x9A
        db      0xCF
        db      0
.data   dw      0xFFFF
        dw      0
        db      0
        db      0x92
        db      0xCF
        db      0
.tss    dw      0xFFFF
        dw      0
        db      0
        db      0x89
        db      0xCF
        db      0
.end:

gdtr:
.size   dw      gdt.end - gdt
.base   dd      gdt

; Uninitialized Data
section .bss
__drive resb    1
__tries resb    1

section .text
boot:   mov     byte [__drive], dl      ; Store Drive Number
        mov     ax, 0x07C0              ; Initialize stack segment
        mov     ss, ax
        mov     sp, 0x03FE              ; Set top of stack
        xor     ax, ax
        mov     ds, ax                  ; Set data segment to 0x0000
        mov     byte [__tries], al      ; Initialize attempt count
        mov     al, 0x03                ; Set default video mode (text|80x25)
        int     0x10                    ; Call video interrupt.
.read:  mov     ah, 0x02                ; BIOS Read function (2)
        mov     al, byte [__sector_count]       ; Number of sectors to read
        mov     ch, 0x00                ; Cylinder (0)
        mov     cl, byte [__sector_start]       ; Starting sector
        mov     dh, 0x00                ; Head
        mov     dl, byte [__drive]
        mov     bx, 0x0800              ; Set buffer location to 0x0800:0x0000
        mov     es, bx
        xor     bx, bx
        int     0x13                    ; Load to es:bx
        mov     al, byte [__tries]      ; Increment attempt count
        inc     al
        mov     byte [__tries], al
        jc      .error
        in      al, 0x92                ; Fast A20 Gate Open
        or      al, 2
        out     0x92, al
.okay:  call    do_e820                 ; Populate memory map
        cli                             ; Disable interrupts
        lgdt    [gdtr]                  ; Load the GDT
        mov     eax, cr0                ; Get CPU flags
        or      eax, 1                  ; Set CPU to protected mode
        mov     cr0, eax                ; Store the CPU flags
        jmp     0x08:pmode              ; Jump into protected mode, flags become active
.error: xor     ax, ax
        xor     dx, dx
        int     0x13                    ; Reset disk drive
        mov     al, byte [__tries]      ; Quit after 3 attempts
        cmp     al, 3
        je      .quit
        jmp     .read                   ; Retry
.quit:  cli                             ; Give up
        hlt
do_e820:xor     ax, ax
        mov     es, ax                  ; Set ES to 0x0000
        mov     di, word [__smap]       ; Set di to 4 + start
        xor     ebx, ebx                ; ebx must be 0 to start
        xor     bp, bp                  ; keep an entry count in bp
        mov     edx, 0x0534D4150        ; Place "SMAP" into edx
        mov     eax, 0xE820
        mov     [es:di + 20], dword 1   ; force a valid ACPI 3.X entry
        mov     ecx, 24                 ; ask for 24 bytes
        int     0x15
        jc      short .failed           ; carry set on first call means "unsupported function"
        mov     edx, 0x0534D4150        ; Some BIOSes apparently trash this register?
        cmp     eax, edx                ; on success, eax must have been reset to "SMAP"
        jne     short .failed
        test    ebx, ebx                ; ebx = 0 implies list is only 1 entry long (worthless)
        je      short .failed
        jmp     short .jmpin
.e820lp:mov     eax, 0xE820             ; eax, ecx get trashed on every int 0x15 call
        mov     [es:di + 20], dword 1   ; force a valid ACPI 3.X entry
        mov     ecx, 24                 ; ask for 24 bytes again
        int     0x15
        jc      short .e820f            ; carry set means "end of list already reached"
        mov     edx, 0x0534D4150        ; repair potentially trashed register
.jmpin: jcxz    .skip                   ; skip any 0 length entries
        cmp     cl, 20                  ; got a 24 byte ACPI 3.X response?
        jbe     short .notext
        test    byte [es:di + 20], 1    ; if so: is the "ignore this data" bit clear?
        je      short .skip
.notext:mov     ecx, [es:di + 8]        ; get lower uint32_t of memory region length
        or      ecx, [es:di + 12]       ; "or" it with upper uint32_t to test for zero
        jz      .skip                   ; if length uint64_t is 0, skip entry
        inc     bp                      ; got a good entry: ++count, move to next storage spot
        add     di, 24
.skip:  test    ebx, ebx                ; if ebx resets to 0, list is complete
        jne     short .e820lp
.e820f: mov     word [__map_ent], bp    ; store the entry count
        clc                             ; there is "jc" on end of list to this point, so the carry must be cleared
        ret
.failed:stc                             ; "function unsupported" error exit
        ret

[BITS 32]
pmode:  mov     ax, 0x10                ; Setting up base state for protected mode
        mov     ds, ax
        mov     es, ax
        mov     fs, ax
        mov     gs, ax
        mov     ss, ax
        mov     eax, 0x7BFC             ; Move the stack pointer to a more favorable
        mov     esp, eax                ;  location.
        call    _init                   ; Run global C++ constructors
        call    k_main                  ; Kernel Main
        call    _fini                   ; Run global C++ deconstructors
        cli                             ; Stop Interrupts
        hlt                             ; Stop CPU

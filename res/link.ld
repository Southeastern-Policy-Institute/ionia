OUTPUT_FORMAT(binary)
SECTIONS
{
  .boot 0x7C00 : AT (0) {
    *boot.o(.text)
    *boot.o(.data)
    . = 0x1FE;
    SHORT(0xAA55)
  } = 0

  .bss 0x7E00 : AT (0x200) {
    *(.bss)
    PROVIDE (__map_ent = .);
  }

  .kernel 0x8000 : AT (0x400) {
    PROVIDE (__kernel_start = .);
    KEEP (*(SORT_NONE(.init)))
    *(.text .text.* .gnu.linkonce.t.*)
    KEEP (*(SORT_NONE(.fini)))

    *(.rodata .rodata.* .gnu.linkonce.r.*)

    . = (. + 3) & ~ 3;
    PROVIDE (__preinit_array_start = .);
    *(.preinit_array)
    PROVIDE (__preinit_array_end = .);
    PROVIDE (__init_array_start = .);
    *(.init_array)
    PROVIDE (__init_array_end = .);
    PROVIDE (__fini_array_start = .);
    *(.fini_array)
    PROVIDE (__fini_array_end = .);

    *(.data .data.* .gnu.linkonce.d.*)
    SORT (CONSTRUCTORS)

    KEEP (*crtbegin.o(.ctors))
    KEEP (*(EXCLUDE_FILE (*crtend.o ) .ctors))
    KEEP (*(SORT(.ctors.*)))
    KEEP (*(.ctors))
    KEEP (*crtbegin.o(.dtors))
    KEEP (*(EXCLUDE_FILE (*crtend.o ) .dtors))
    KEEP (*(SORT(.dtors.*)))
    KEEP (*(.dtors))
    
    . = (. + 3) & ~ 3;
    PROVIDE (__kernel_end = .);
    /* This makes sure the allocator doesn't get confused */
    LONG(0)
    LONG(0)
    
    . = 0x167BFF - 0x400;
    BYTE(0xFF)
  } = 0x90909090

  /DISCARD/ : { *(*) }

  PROVIDE (__sector_count = (((__kernel_end - __kernel_start) + 511) & ~ 511) / 512);
  PROVIDE (__sector_start = 3);
}
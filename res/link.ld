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
    *(.text .text.* .gnu.linkonce.t.*)

    . = (. + 3) & ~ 3;
    *(.rodata .rodata.* .gnu.linkonce.r.*)

    . = (. + 3) & ~ 3;
    *(.data .data.* .gnu.linkonce.d.*)
    SORT (CONSTRUCTORS)

    PROVIDE (__ctors_start = .);
    KEEP (*(.ctors))
    PROVIDE (__ctors_end = .);
    PROVIDE (__dtors_start = .);
    KEEP (*(.dtors))
    PROVIDE (__dtors_end = .);
    
    . = (. + 3) & ~ 3;
    PROVIDE (__kernel_end = .);
    /* This makes sure the allocator doesn't get confused */
    LONG(0)
    LONG(0)
    
    . = 0x1677FF;
    BYTE(0xFF)
  } = 0x90909090

  /DISCARD/ : { *(*) }

  PROVIDE (__sector_count = (((__kernel_end - __kernel_start) + 511) & ~ 511) / 512);
  PROVIDE (__sector_start = 3);
}
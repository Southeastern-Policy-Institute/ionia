OUTPUT_FORMAT(binary)
SECTIONS
{
  .boot 0x7C00 : AT (0) {
    *boot.o(.text)

    . = (. + 3) & ~ 3;
    *boot.o(.data)

    . = (. + 3) & ~ 3;
    __sector_count = .;
    LONG((((__kernel_end - __kernel_start) + 511) & ~ 511) / 512)
    __sector_start = .;
    LONG(3)
    __smap_size = .;
    LONG((__kernel_start - (__map_ent + 4)) / 24)
    __smap = .;
    LONG(__map_ent + 4)
    __mem_start = .;
    LONG(0x100000);
    __mem_max = .;
    LONG(0)

    /* Boot Sector Signature */
    . = 0x1FE;
    SHORT(0xAA55)
  } = 0

  /* Sector 2 reserved for uninitialized data */
  .bss 0x7E00 : AT (0x200) {
    *boot.o(.bss)
    __map_ent = .;
  }

  .kernel 0x8000 : AT (0x400) {
    __kernel_start = .;
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
    __kernel_end = .;
    /* This makes sure the allocator doesn't get confused */
    LONG(0)
    LONG(0)

    *(.bss)

    . = 0x1677FF;
    BYTE(0xFF)
  } = 0x90909090

  /DISCARD/ : { *(*) }
}

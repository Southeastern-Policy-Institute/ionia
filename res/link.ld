OUTPUT_FORMAT(binary)
SECTIONS
{
  .boot 0x7C00 : AT (0) {
    *boot.o(.text)

    . = (. + 3) & ~ 3;
    *boot.o(.data)

    . = (. + 3) & ~ 3;
    __sector_count = .;
    LONG((__kernel_end - __kernel_start) / 512)
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
    __errno = .;
    LONG(0)

    /* Boot Sector Signature */
    . = 0x1FE;
    SHORT(0xAA55)
  } = 0

  /* Sector 2 reserved for uninitialized data */
  .bss 0x7E00 : AT (0x200) {
    *boot.o(.bss)
    . = ALIGN(8);
    __map_ent = .;
  }

  .kernel 0x8000 : AT (0x400) {
    __kernel_start = .;
    KEEP (*(.text .text.* .gnu.linkonce.t.*))

    . = ALIGN (8);
    KEEP (*(.rodata .rodata.* .gnu.linkonce.r.*))

    . = ALIGN (8);
    KEEP (*(.data .data.* .gnu.linkonce.d.*))
    SORT (CONSTRUCTORS)

    PROVIDE (__ctors_start = .);
    KEEP (*(.ctors))
    PROVIDE (__ctors_end = .);
    PROVIDE (__dtors_start = .);
    KEEP (*(.dtors))
    PROVIDE (__dtors_end = .);

    . = ALIGN (512);
    __kernel_end = .;

    *(.bss)

    . = 0x1677FF;
    BYTE(0xFF)
  } = 0x90909090

  /* BIOS Data */
  __bios_com1 = 0x0400;
  __bios_com2 = 0x0402;
  __bios_com3 = 0x0404;
  __bios_com4 = 0x0406;
  __bios_lpt1 = 0x0408;
  __bios_lpt2 = 0x040A;
  __bios_lpt3 = 0x040C;
  __bios_ebda = 0x040E; /* EBDA base address >> 4 */
  __bios_memk = 0x0413; /* # of kilobytes before EBDA */
  __bios_kbst = 0x0417; /* Keyboard state flags */
  __bios_keyb = 0x041E; /* Keyboard buffer */
  __bios_disp = 0x0449; /* Display mode */
  __bios_cols = 0x044A; /* Number of columns in text mode */
  __bios_vid0 = 0x0463; /* Video IO port */
  __bios_tick = 0x046C; /* # of IRQ0 ticks since boot */
  __bios_hdds = 0x0475; /* # of HDD's detected */
  __bios_kbsh = 0x0497; /* Last keyboard LED/Shift state */

  /DISCARD/ : { *(*) }
}

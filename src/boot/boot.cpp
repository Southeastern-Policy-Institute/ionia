
# include <stdint.h>
# include <sys/port.hpp>
# include <sys/boot.hpp>

extern "C"
void _init (void);

__attribute__ ((section(".data")))
GDT_ENTRY gdt[] {
  {0, 0, 0, 0, 0, 0},             // Null Entry
  {0xFFFF, 0, 0, 0x9A, 0xCF, 0},  // Code
  {0xFFFF, 0, 0, 0x92, 0xCF, 0},  // Data
  {0xFFFF, 0, 0, 0x89, 0xCF, 0},  // TSS
};

__attribute__ ((section(".data")))
GDTR gdtr {
  sizeof (gdt), reinterpret_cast<uint32_t> (&gdt)
};

__attribute__ ((section(".bss")))
uint8_t __drive;

inline
int detect_memory (smap_entry_t* buffer, int max_entries) {

  uint32_t content_id = 0, signature = 0, bytes = 0;
  uint16_t entries = 0;

  do {
    // Attempt to populate an entry of the memory map
    asm volatile ("int $0x15"
                : "=a" (signature),
                  "=b" (content_id),
                  "=c" (bytes)
                : "a" (0xE820),
                  "b" (content_id),
                  "c" (24),
                  "d" (0x534D4150),
                  "D" (buffer));
    if (signature != 0x534D4150)
      return -1;  // Error!
    if (bytes > 20 && !(buffer->ACPI & 1)) { /* Ignore this entry */ }
    else {
      buffer++;
      entries++;
    };
  } while (content_id && entries < max_entries);

  return entries;

};

extern "C" __attribute__ ((naked, noinline))
void start (void) {


  // Store drive number
  asm volatile ("mov %%dl, %0" : "=m" (__drive));

  // Set stack segment
  asm volatile ("mov %0, %%ss" : : "r" (0x07C0));

  // Set top of stack
  asm volatile ("mov %0, %%sp" : : "i" (0x03FE));

  // Set data segment
  asm volatile ("mov %0, %%ds" : : "r" (0));

  // Set extra segment
  asm volatile ("mov %0, %%es" : : "r" (0));

  // Set video mode (text|80x25)
  asm volatile ("int $0x10" : : "a" (0x03));

  // Attempt to read from disk
  uint16_t status;
  uint8_t tries = 0;
  do {
    asm volatile ("int $0x13"
                : "=a" (status)
                : "a" ((2 << 8) | reinterpret_cast<uintptr_t> (&__sector_count)),
                  "b" (0x8000),
                  "c" (&__sector_start),
                  "d" (__drive)
                : "memory", "cc");
  } while ((status >> 8) && tries++ < 3);

  // Enable A20 Gate
  sys::outb (0x92, sys::inb (0x92) | 2);

  // Detect available memory
  __map_ent = detect_memory (__smap, reinterpret_cast<uintptr_t> (&__smap_size));

  // Disable interrupts
  asm volatile ("cli");

  // Load GDT
  asm volatile ("lgdt %0" : : "m" (gdtr));

  // Set CR0 for protected mode
  asm volatile ("mov %%cr0, %%eax\n"
                "or $1, %%al\n"
                "mov %%eax, %%cr0"
              :
              :
              : "%eax");

  // Set up segment registers
  asm volatile ("mov %%ds, %0\n"
                "mov %%es, %0\n"
                "mov %%fs, %0\n"
                "mov %%gs, %0\n"
                "mov %%ss, %0"
              :
              : "r" (0x10));

  // Relocate stack pointer to somewhere more favorable
  asm volatile ("mov %0, %%esp" : : "r" (0x7BFC));

  // Segment jump to protected mode!
  asm volatile ("jmpl $0x08,$_init");
};

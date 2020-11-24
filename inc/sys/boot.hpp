/* BOOT.HPP - Declarations for BootLoader
 * Southeastern Policy Institute, 2020
 */

# if !defined(__BOOT_HPP__) && defined(__cplusplus)
#   define  __BOOT_HPP__
#   include <stdint.h>

typedef struct SMAP_ENTRY {

  uint32_t BaseL;   // base address uint64_t
  uint32_t BaseH;
  uint32_t LengthL; // length uint64_t
  uint32_t LengthH;
  uint32_t Type;    // entry Type
  uint32_t ACPI;    // extended

} __attribute__((packed)) smap_entry_t;

struct GDT_ENTRY {
  uint16_t limit, baseL;
  uint8_t baseM, access, flag_limit, baseH;
} __attribute__ ((packed));

struct GDTR {
  uint16_t size;
  uint32_t base;
} __attribute__ ((packed));

extern "C" {

  extern void* __kernel_start[0];

  extern void* __kernel_end[0];

  extern uint16_t __map_ent;

  extern uint32_t __sector_count;

  extern uint32_t __sector_start;

  extern uint32_t __smap_size;

  extern smap_entry_t* __smap;

};

# endif /* __BOOT_HPP__ */

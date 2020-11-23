/* BOOT.HPP - Declarations for BootLoader
 * Southeastern Policy Institute, 2020
 */

# if !defined(__BOOT_HPP__) && defined(__cplusplus)
#   define  __BOOT_HPP__
#   include <stdint.h>

extern "C" void* __kernel_end;
extern "C" uint32_t __map_ent;

typedef struct SMAP_ENTRY {

  uint32_t BaseL;   // base address uint64_t
  uint32_t BaseH;
  uint32_t LengthL; // length uint64_t
  uint32_t LengthH;
  uint32_t Type;    // entry Type
  uint32_t ACPI;    // extended

} __attribute__((packed)) smap_entry_t;

# endif /* __BOOT_HPP__ */

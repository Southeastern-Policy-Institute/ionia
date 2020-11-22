/* BOOT.H - Declarations for BootLoader
 * Claudia, 2020
 */

# ifndef  __BOOT_H__
#   define  __BOOT_H__
#   include <stdint.h>
#   include "../common.h"

EXTERN void* __kernel_end;
EXTERN uint32_t __map_ent;

typedef struct SMAP_ENTRY {

  uint32_t BaseL;   // base address uint64_t
  uint32_t BaseH;
  uint32_t LengthL; // length uint64_t
  uint32_t LengthH;
  uint32_t Type;    // entry Type
  uint32_t ACPI;    // extended

} __attribute__((packed)) smap_entry_t;

# endif /* __BOOT_H__ */

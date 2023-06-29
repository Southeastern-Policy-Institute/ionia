/* BOOT.HPP - Declarations for BootLoader
 * Southeastern Policy Institute, 2023
 */

# if !defined(__BOOT_HPP__) && defined(__cplusplus)
#   define  __BOOT_HPP__
#   include <stdint.h>
#   define  UINT64_UNION(name)  union {                       \
                                  struct {                    \
                                    uint32_t name##L;         \
                                    uint32_t name##H;         \
                                  } __attribute__ ((packed)); \
                                  uint64_t name;              \
                                }

namespace sys {

  typedef struct SMAP_ENTRY {
    UINT64_UNION (Base);
    UINT64_UNION (Length);
    uint32_t Type;    // entry Type
    uint32_t ACPI;    // extended
  } __attribute__ ((packed)) smap_entry_t;

  struct GDT_ENTRY {
    uint16_t limit, baseL;
    uint8_t baseM, access, flag_limit, baseH;
  } __attribute__ ((packed));

  struct GDTR {
    uint16_t size;
    uint32_t base;
  } __attribute__ ((packed));

  extern "C" {

    extern
    void* __kernel_start[0];

    extern
    void* __kernel_end[0];

    extern const volatile
    uint16_t __map_ent;

    extern const volatile
    uint32_t __sector_count;

    extern const volatile
    uint32_t __sector_start;

    extern const volatile
    uint32_t __smap_size;

    extern const volatile
    smap_entry_t* __smap;

    extern const volatile
    uint16_t __bios_com1;

    extern const volatile
    uint16_t __bios_com2;

    extern const volatile
    uint16_t __bios_com3;

    extern const volatile
    uint16_t __bios_com4;

    extern const volatile
    uint16_t __bios_lpt1;

    extern const volatile
    uint16_t __bios_lpt2;

    extern const volatile
    uint16_t __bios_lpt3;

    extern const volatile
    uint16_t __bios_ebda;

    extern const volatile
    uint16_t __bios_memk;

    extern const volatile
    uint16_t __bios_kbst;

    extern const volatile
    char __bios_keyb[32];

    extern const volatile 
    uint8_t __bios_disp;

    extern const volatile
    uint16_t __bios_cols;

    extern const volatile
    uint16_t __bios_vid0;

    extern const volatile
    uint16_t __bios_tick;

    extern const volatile
    uint8_t __bios_hdds;

    extern const volatile
    uint8_t __bios_kbsh;

  };

};

#   undef UINT64_UNION
# endif /* __BOOT_HPP__ */

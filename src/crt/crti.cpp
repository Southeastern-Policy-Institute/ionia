/* CRTI.CPP - C Runtime Startup
 * Southeastern Policy Institute, 2020
 */

# include <sys/boot.hpp>

extern "C"
void k_main (void);

extern "C"
void _fini (void);

typedef void (*ctor_ptr) (void);

// These are defined by the linker script
extern "C"
ctor_ptr __ctors_start[0], __ctors_end[0];

extern "C"
void _init (void) {
  for (ctor_ptr* func = __ctors_start; func != __ctors_end; func++)
    (*func)();
};

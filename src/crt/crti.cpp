/* CRTI.CPP - C Runtime Startup
 * Southeastern Policy Institute, 2020
 */

# include <sys/boot.hpp>

typedef void (*ctor_ptr) (void);

extern "C"
ctor_ptr __ctors_start[0], __ctors_end[0];

smap_entry_t* smap = reinterpret_cast<smap_entry_t*>
  (reinterpret_cast<uintptr_t> (&__map_ent) + 4);

extern "C"
void _init (void) {
  for (ctor_ptr* func = __ctors_start; func != __ctors_end; func++)
    (*func)();
};

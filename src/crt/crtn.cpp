/* CRTN.CPP - C Runtime Deconstructors
 * Southeastern Policy Institute, 2020
 */

# include <sys/boot.hpp>

typedef void (*dtor_ptr) (void);

extern "C"
dtor_ptr __dtors_start[0], __dtors_end[0];

extern "C"
void _fini (void) {
  for (dtor_ptr* func = __dtors_start; func != __dtors_end; func++)
    (*func)();
};

/* ICXXABI.CPP - GCC ABI Implementation
 * Southeastern Policy Institute, 2020
 */

#include <sys/icxxabi.h>

namespace __cxxabiv1 {
  extern "C" {

    atexit_func_entry_t __atexit_funcs[ATEXIT_MAX_FUNCS];
    uarch_t __atexit_func_count = 0;

    /* for virtual functions */
    void __cxa_pure_virtual () {};

    int __cxa_guard_acquire (__guard* g) { return !*(char*)g; };

    void __cxa_guard_release (__guard* g) { *(char*)g = 1; };

    void __cxa_guard_abort (__guard*) {};

    int __cxa_atexit(destructor_func_t f, void* objptr, void* dso) {
      if (__atexit_func_count >= ATEXIT_MAX_FUNCS)
        return -1;

      __atexit_funcs[__atexit_func_count].destructor_func = f;
      __atexit_funcs[__atexit_func_count].obj_ptr = objptr;
      __atexit_funcs[__atexit_func_count].dso_handle = dso;
      __atexit_func_count++;

      return 0;
    };

    void __cxa_finalize(void* f) {
      uarch_t i = __atexit_func_count;

      if (!f) {

        while (i--)
          if (__atexit_funcs[i].destructor_func)
            (*__atexit_funcs[i].destructor_func)(__atexit_funcs[i].obj_ptr);

      } else {

        while (i--)
          if (__atexit_funcs[i].destructor_func == f) {
            (*__atexit_funcs[i].destructor_func)(__atexit_funcs[i].obj_ptr);
            __atexit_funcs[i].destructor_func = 0;
          };

      };
    };

  };
};
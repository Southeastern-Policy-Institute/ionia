/* ICXXABI.HPP - GCC ABI Implementation
 * Southeastern Policy Institute, 2020
 */

# if !defined(_ICXXABI_HPP_) && defined(__cplusplus)
#   define _ICXXABI_HPP_
#   define ATEXIT_MAX_FUNCS 128u
#   ifdef __cplusplus
namespace __cxxabiv1 {
  extern "C" {
#   endif /* __cplusplus */

    typedef unsigned uarch_t;

    typedef void (*destructor_func_t) (void*);

    typedef struct ATEXIT_FUNC_ENTRY {
      destructor_func_t destructor_func;
      void* obj_ptr;
      void* dso_handle;
    } atexit_func_entry_t;

    __extension__ typedef int __guard __attribute__((mode(__DI__)));

    int __cxa_atexit (destructor_func_t, void*, void*);
    void __cxa_finalize (void*);

#   ifdef __cplusplus
  };
};
#   endif /* __cplusplus */
# endif /* _ICXXABI_HPP_ */

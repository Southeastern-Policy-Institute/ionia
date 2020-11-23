/* MEM.H - Kernel Memory Management
 * Southeastern Policy Institute, 2020
 */

# if !defined(_MEM_H_) && defined(__cplusplus)
#   define  _MEM_H_
#   include <stdint.h>
#   include "boot.hpp"

namespace sys {
  
  struct MEM_BLOCK {
    static MEM_BLOCK* MEM_START;
    static MEM_BLOCK* MEM_MAX;
    MEM_BLOCK* next;
    bool used;

    inline
    __SIZE_TYPE__ size (void) const {
      uintptr_t _next = reinterpret_cast<uintptr_t> (next);
      uintptr_t _this = reinterpret_cast<uintptr_t> (this);
      return _next
        ? _next - (_this + sizeof (MEM_BLOCK))
        : 0;
    };

    inline
    uintptr_t start (void) const {
      uintptr_t _this = reinterpret_cast<uintptr_t> (this);
      return _this + sizeof (MEM_BLOCK);
    };
  } __attribute__ ((packed));

};
# endif /* _MEM_H_ */

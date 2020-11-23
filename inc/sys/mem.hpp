/* MEM.H - Kernel Memory Management
 * Claudia, 2020
 */

# if !defined(_MEM_H_) && defined(__cplusplus)
#   define  _MEM_H_
#   include <stdint.h>
#   include "boot.h"
namespace sys {
  
  struct MEM_BLOCK {
    static MEM_BLOCK* MEM_START;
    MEM_BLOCK* next;
    bool used;

    inline __SIZE_TYPE__ size (void) const {
      return next
        ? ((uintptr_t)next) - (((uintptr_t)this) + sizeof (MEM_BLOCK))
        : 0;
    };

    inline uintptr_t start (void) const {
      return ((uintptr_t)this) + sizeof (MEM_BLOCK);
    };
  } __attribute__ ((packed));

};
# endif /* _MEM_H_ */

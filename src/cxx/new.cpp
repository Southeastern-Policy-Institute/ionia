/* NEW.CPP - Kernel Memory Allocator
 * Southeastern Policy Institute, 2020
 */

# include <sys/mem.hpp>
# include <algorithm.hpp>

using sys::MEM_BLOCK;

MEM_BLOCK* MEM_BLOCK::MEM_START = (MEM_BLOCK*)&__kernel_end;

MEM_BLOCK* MEM_BLOCK::MEM_MAX = MEM_BLOCK::MEM_START + 50;

void* operator new (__SIZE_TYPE__ len) {
  MEM_BLOCK* target;
  MEM_BLOCK* temp;

  // If no size is specified, return NULL.
  // Make sure -fcheck-new is set!
  if (!len)
    return nullptr;

  // Itterate over the blocks
  for ( target = MEM_BLOCK::MEM_START;
        target->next;
        target = target->next )
  { //  Perform data reclaimation if applicable...
    //  Split:
    //    If the target block is not used, and its size is more than what
    //    is required...
    if (!target->used && (target->size () >= len)) {
      //  Check if the block is large enough to split...
      if (target->size () > (sizeof (MEM_BLOCK) + len + 1)) {
        //  Store destination link.
        temp = target->next;
        //  Generate new split link and return target.
        target->next = (MEM_BLOCK*)((uintptr_t)target->start () + len);
        target->next->next = temp;
        target->next->used = false;
        goto done;
      }
      //  Otherwise, escape.
      else {
        goto done;
      };
    };

  };

  //  If we get here, we are at the end of the linked list.
  //  Set the 'next' pointer to what will become the new terminator.
  target->next = (MEM_BLOCK*)((uintptr_t)target->start () + len);
  //  Set up the new terminator.
  target->next->next = nullptr;
  target->next->used = false;

  //  Common exit point; Set used flag and update last_alloc.
done:
  target->used = true;
  return reinterpret_cast<void*> (target->start ());
};

void* operator new[](__SIZE_TYPE__ size) {
  return
    ionia::memset<uint8_t> (
      reinterpret_cast<uint8_t*> (operator new (size)),
      0,
      size
    );
};


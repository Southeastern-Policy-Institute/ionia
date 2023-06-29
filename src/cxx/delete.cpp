/* DELETE.CPP - Kernel Memory Deallocator
 * Southeastern Policy Institute, 2023
 */

# include <sys/mem.hpp>

using sys::MEM_BLOCK;

void operator delete (void* loc) {
  MEM_BLOCK* previous, * target;

  if (!loc)
    return;

  //  Itterate over the blocks
  for ( previous = nullptr, target = sys::__mem_start;
        target->next;
        previous = target, target = target->next
  ) {
    //  Collate unused memory blocks
    if (previous && (!target->used && !previous->used))
      previous->next = target->next;
    //  Flag specified block as unused
    if (target->start () == reinterpret_cast<uintptr_t> (loc)) {
      target->used = false;
    };
  };

  //  Target now points to terminator, previous is last actual block
  //  If it is not used, make it the new terminator
  if (previous && !previous->used)
    previous->next = nullptr;
};

void operator delete[] (void* p) {
  operator delete (p);
};

/* MEMORY.CPP - Implements memory allocation routines
 * Southeastern Policy Institute, 2020
 */

# include <stdlib.h>
# include <sys/mem.hpp>         // sys::__mem_start

using sys::MEM_BLOCK;

extern "C" __attribute__ ((returns_nonnull, nothrow))
void* std::malloc (size_t len) {
  return new __UINT8_TYPE__[len];
};

extern "C" __attribute__ ((returns_nonnull, nothrow))
void* std::calloc (size_t size, size_t count) {
  return new __UINT8_TYPE__[size * count];
};

extern "C" __attribute__ ((returns_nonnull, nonnull, nothrow))
void* std::realloc (void* old, size_t new_size) {

  // Internal copying routine
  auto memcpy = [] (void* dest, const void* src, __SIZE_TYPE__ len) -> void* {
    __UINT8_TYPE__* cdest = reinterpret_cast<__UINT8_TYPE__*> (dest);
    const __UINT8_TYPE__* csrc = reinterpret_cast<const __UINT8_TYPE__*> (src);
    while (len--)
      *cdest++ = *csrc++;
    return dest;
  };

  MEM_BLOCK* target;
  size_t old_size = 0;
  void* output = old;

  //  Itterate over the blocks
  for ( target = sys::__mem_start;
        target->next;
        target = target->next)
    // Determine size of target memory block
    if (target->start () == reinterpret_cast<uintptr_t> (old))
      old_size = target->size ();

  // Do not attempt to reallocate to a smaller size
  if (new_size <= old_size)
    return output;

  // Allocate new space
  output = new __UINT8_TYPE__[new_size];

  // Copy old memory into the new space
  memcpy (output, old, old_size);

  // Destroy old memory block
  delete reinterpret_cast<__UINT8_TYPE__*> (old);

  return output;

};

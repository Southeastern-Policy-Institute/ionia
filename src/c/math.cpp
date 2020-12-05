/* MATH.CPP - Implements math functions
 * Southeastern Policy Institute, 2020
 */

# include <stdlib.h>

extern "C" __attribute__ ((regparm(1), nothrow))
__UINT32_TYPE__ std::abs (__INT32_TYPE__ n) {
  // Clears the negative bit
  asm volatile ("btrl\t%1, %0"
              : "=m" (n)
              : "Ir" (31)
              : "cc");
  return n;
};

extern "C" __attribute__ ((regparm(2), nothrow))
std::div_t std::div (__INT32_TYPE__ num, __INT32_TYPE__ den) {
  div_t out;
  asm volatile ("div\t%%ecx"
              : "=a" (out.quotient), "=d" (out.remainder)
              : "A" (num), "c" (den));
  return out;
};

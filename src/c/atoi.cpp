/* ATOI.CPP - Parses a string representation of an integer
 * Southeastern Policy Institute, 2020
 */

# include <stdlib.h>

extern "C" __attribute__ ((nonnull, nothrow))
__INT32_TYPE__ std::atoi (const char* str) {

  __INT32_TYPE__ output = 0;

  // Internal routine to produce powers of 10
  auto pow10 = [] (__UINT32_TYPE__ val) -> __UINT32_TYPE__ {
    __UINT32_TYPE__ __output = 1;
    while (val--)
      __output *= 10;
    return __output;
  };

  // Internal strlen (to avoid cross-cutting concerns)
  auto strlen = [] (const char* str) -> size_t {
    size_t __output = 0;
    while (*str++)
      __output++;
    return __output;
  };

  // Make output negative if called for
  if (*str == '-') {
    output |= (1U << 31);
    ++str;
  };

  // Parse the digits from right to left
  for ( __SIZE_TYPE__ i = strlen (str) - 1, j = 0
      ; j < strlen (str)
      ; i--, j++)
    output += ('0' - str[i]) * pow10 (j);

  return output;
};

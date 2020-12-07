/* ATOI.CPP - Parses a string representation of an integer
 * Southeastern Policy Institute, 2020
 */

# include <stdlib.h>

extern "C" __attribute__ ((nonnull, nothrow))
int std::atoi (const char* str) {

  // `output` is unsigned to make sure we are able to manipulate the sign-
  // bit without confusing the compiler
  unsigned int output = 0;

  // Internal routine to produce powers of 10
  auto pow10 = [] (unsigned int val) -> unsigned int {
    unsigned int __output = 1;
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

  // Set the sign-bit and advance the pointer position if negative
  if (*str == '-') {
    output |= (1U << 31);
    ++str;
  };

  // Parse the digits from right to left
  for ( size_t i = strlen (str) - 1, j = 0
      ; j < strlen (str)
      ; i--, j++)
    output += (str[i] - '0') * pow10 (j);

  return output;

};

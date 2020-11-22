/* ITOA.C - Convert a number to string.
 * Southeastern Policy Institute, 2020
 */

# include <stdint.h>

typedef enum FLAG {
  FLAG_CAPS = 1,
  FLAG_LEAD_ZERO = 2
} flag_t;

__attribute__((noinline))
const char* itoa (int32_t num, uint32_t base) {
  static uint16_t flags = FLAG_CAPS | FLAG_LEAD_ZERO;
  static uint8_t number_width = 4;
  static char buffer[25];
  uint32_t i = 0;
  uint8_t neg = 0;

  if (!num) {
    // Add leading spaces/zeros
    while ((number_width-1) > i)
      buffer[i++] = flags & FLAG_LEAD_ZERO ? '0' : ' ';
    buffer[i++] = '0';
    buffer[i] = '\0';
    return buffer;
  };

  if (num < 0 && base == 10) {
    neg = 0xFF;
    num = -num;
  };

  while (num) {
    int rem = num % base;
    buffer[i++] = rem > 9
      ? (rem-10) + (flags & FLAG_CAPS ? 'A' : 'a')
      : rem + '0';
    num /= base;
  };

  // Add leading spaces/zeros
  while (number_width > i)
    buffer[i++] = flags & FLAG_LEAD_ZERO ? '0' : ' ';

  if (neg)
    buffer[i++] = '-';

  buffer[i] = '\0';

  for (uint32_t j = 0; j < --i; j++) {
    register char c = buffer[j];
    buffer[j] = buffer[i];
    buffer[i] = c;
  };

  return buffer;

};
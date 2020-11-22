/* SPRINTF.C - Print a formatted string to a buffer.
 * Southeastern Policy Institute, 2020
 */

# include <stdint.h>
# include <stdarg.h>
# define ZERO(val,n) (                                              \
{ unsigned int __ret = val;                                         \
  asm volatile ("btsl %1, %0" : "=m" (__ret) : "Ir" (n) : "cc");    \
  __ret;                                                            \
})

typedef enum FLAG {
  FLAG_CAPS = 1,
  FLAG_LEAD_ZERO = 2,
  FLAG_FMT_INTERNAL = 4
} flag_t;

static uint16_t flags = FLAG_CAPS | FLAG_LEAD_ZERO;

static uint8_t number_width = 8;

__SIZE_TYPE__ sprintf_s (char* dest, const char* str) {
  register __SIZE_TYPE__ bytes_written;
  for (bytes_written = 0; *str; bytes_written++)
    *dest++ = *str++;
  return bytes_written;
};

__attribute__((noinline))
__SIZE_TYPE__ sprintf_itoa (char* buffer, int32_t num, uint32_t base) {
  __SIZE_TYPE__ i = 0;
  uint8_t neg = 0;

  if (!num) {
    // Add leading spaces/zeros
    while ((number_width-1) > i)
      buffer[i++] = flags & FLAG_LEAD_ZERO ? '0' : ' ';
    buffer[i++] = '0';
    return i;
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

  __SIZE_TYPE__ written = i;

  // Reverse output+
  for (uint32_t j = 0; j < --i; j++) {
    register char c = buffer[j];
    buffer[j] = buffer[i];
    buffer[i] = c;
  };

  return written;

};

__attribute__ ((noinline))
__SIZE_TYPE__ sprintf (char* str, const char* format, ...) {

  va_list ap;
  __SIZE_TYPE__ bytes_written;

  va_start (ap, format);
  for (bytes_written = 0; *format; format++) {
    switch (*format) {
    case '%':
      
    case 'S':
    case 's':
      bytes_written += sprintf_s (
        str + bytes_written, va_arg (ap, const char*)
      );
      break;
    case 'X':
      flags |= FLAG_CAPS;
    case 'x':
      bytes_written += sprintf_itoa (
        str + bytes_written, va_arg (ap, uint32_t), 16
      );
      break;
    case 'd':
    case 'i':
      bytes_written += sprintf_itoa (
        str + bytes_written, va_arg (ap, int32_t), 10
      );
      break;
    default:
      str[bytes_written++] = *format;
      break;
    };
  };

  va_end (ap);
  str[bytes_written++] = '\0';
  return bytes_written;

};


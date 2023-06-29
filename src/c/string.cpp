/* STRING.CPP - Implements string manipulation routines
 * Southeaster Policy Institute, 2023
 */

# include <string.h>

extern "C" __attribute__ ((nonnull, returns_nonnull, nothrow))
void* std::memcpy (void* dest, const void* src, size_t len) {

  __UINT8_TYPE__* cdest = reinterpret_cast<__UINT8_TYPE__*> (dest);
  const __UINT8_TYPE__* csrc = reinterpret_cast<const __UINT8_TYPE__*> (src);

  while (len--)
    *cdest++ = *csrc++;

  return dest;

};

extern "C" __attribute__ ((nonnull, returns_nonnull, nothrow))
void* std::memmove (void* dest, const void* src, size_t len) {

  __UINT8_TYPE__* cdest = reinterpret_cast<__UINT8_TYPE__*> (dest);
  const __UINT8_TYPE__* csrc = reinterpret_cast<const __UINT8_TYPE__*> (src);
  __UINT8_TYPE__* buffer = new __UINT8_TYPE__[len];

  for (size_t i = 0; i < len; i++)
    buffer[i] = csrc[i];

  for (size_t i = 0; i < len; i++)
    cdest[i] = buffer[i];

  delete buffer;
  return dest;

};

extern "C" __attribute__ ((nonnull, returns_nonnull, nothrow))
char* std::strcpy (char* dest, const char* src) {

  char* idest = dest;

  while (*src)
    *dest++ = *src++;

  *dest = '\0';
  return idest;

};

extern "C" __attribute__ ((nonnull, returns_nonnull, nothrow))
char* std::strncpy (char* dest, const char* src, size_t len) {

  char* idest = dest;

  while (len-- && *src)
    *dest++ = *src++;

  *dest = '\0';
  return idest;

};

extern "C" __attribute__ ((nonnull, returns_nonnull, nothrow))
char* std::strcat (char* dest, const char* src) {

  char* idest = dest;
  dest += strlen (dest);

  while (*src)
    *dest++ = *src++;

  *dest = '\0';
  return idest;

};

extern "C" __attribute__ ((nonnull, returns_nonnull, nothrow))
char* std::strncat (char* dest, const char* src, size_t len) {

  char* idest = dest;
  dest += strlen (dest);

  while (len-- && *src)
    *dest++ = *src++;

  *dest = '\0';
  return idest;

};

extern "C" __attribute__ ((nonnull, nothrow))
std::size_t std::strlen (const char* str) {

  size_t output;

  for (output = 0; *str++; output++);

  return output;

};

extern "C" __attribute__ ((nonnull, returns_nonnull, nothrow))
char* std::strchr (const char* str, int c) {

  char* output;

  for (output = const_cast<char*> (str); *output != c && *output; output++);

  return output;

};

extern "C" __attribute__ ((nonnull, nothrow))
int std::strcmp (const char* str1, const char* str2) {

  unsigned int str1_total, str2_total;

  for (str1_total = 0; *str1; str1_total += *str1++);
  for (str2_total = 0; *str2; str2_total += *str2++);

  return str1_total - str2_total;

};

extern "C" __attribute__ ((nonnull, nothrow))
int std::strncmp (const char* str1, const char* str2, size_t len) {

  unsigned int str1_total = 0, str2_total = 0;

  for (size_t i = 0; *str1 && i < len; i++)
    str1_total += *str1++;
  for (size_t i = 0; *str2 && i < len; i++)
    str2_total += *str2++;

  return str1_total - str2_total;

};

extern "C" __attribute__ ((nonnull, returns_nonnull, nothrow))
char* std::strstr (const char* haystack, const char* needle) {

  while (*haystack && strlen (haystack) >= strlen (needle))
    if (!strncmp (needle, haystack, strlen (needle)))
      break;
    else
      haystack++;

  return const_cast<char*> (haystack);

};

/* STRING.CPP - Implements some string manipulation routines.
 * Southeastern Policy Institute, 2020
 */

# include <ionia.hpp>

using ionia::string;

string::Flag string::flags {};

string& string::operator<< (const string& str) {
  tchar_t* temp = new tchar_t[length () + str.length () + 1];
  strcpy (temp, array_);
  strcpy (temp + length (), str.array_);
  delete array_;
  array_ = temp;
  size_ = strlen (array_) + 1;
  return *this;
};

string& string::operator<< (tchar_t c) {
  string temp {length () + 1};
  strcpy (temp.array_, array_);
  temp[length ()] = c;
  operator= (temp);
  return *this;
};

string& string::operator<< (uint32_t num) {
  static tchar_t buffer[25];
  uint32_t base = flags[HEX] ? 16 : 10;
  uint32_t i = 0;
  uint8_t neg = 0;

  if (!num) {
    // Add leading spaces/zeros
    while ((flags.number_width()-1) > i)
      buffer[i++] = flags[ZERO_EXTEND] ? '0' : ' ';
    buffer[i++] = '0';
    buffer[i] = '\0';
    goto done;
  };

  if (num < 0 && base == 10) {
    neg = 0xFF;
    num = -num;
  };

  while (num) {
    int rem = num % base;
    buffer[i++] = rem > 9
      ? (rem-10) + (flags[CAPS] ? 'A' : 'a')
      : rem + '0';
    num /= base;
  };

  // Add leading spaces/zeros
  while (flags.number_width() > i)
    buffer[i++] = flags[ZERO_EXTEND] ? '0' : ' ';

  if (neg)
    buffer[i++] = '-';

  buffer[i] = '\0';

  for (uint32_t j = 0; j < --i; j++) {
    register char c = buffer[j];
    buffer[j] = buffer[i];
    buffer[i] = c;
  };

done:
  return operator<< (string (buffer));
};

string& string::operator<< (const Flag& flag) {
  flags = flag;
  return *this;
};

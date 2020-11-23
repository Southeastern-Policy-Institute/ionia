/* STRING.HPP - Variable-width character string manipulation.
 * Southeastern Policy Institute, 2020
 */

# if !defined(_SPI_STRING_HPP_) && defined(__cplusplus)
#   define  _SPI_STRING_HPP_
#   include "string.h"
#   include "array.hpp"
#   include "algorithm.hpp"
namespace ionia {

  // Variable width NULL terminated string datatype.
  class string : public array<tchar_t> {
  public:

    // Returns the number of characters in a string.
    template<typename T = tchar_t> static inline
    unsigned int strlen (const T* str) {
      unsigned int len;
      if (!str)
        return 0;
      for (len = 0; str[len]; len++);
      return len;
    };

    // String Copy
    template <typename T = tchar_t> static inline
    T* strcpy (T* dest, const T* src) {
      int d0, d1, d2;
#   ifdef UNICODE
      asm volatile ("1:\tlodsw\n\t"
                    "stosw\n\t"
                    "testw %%ax, %%ax\n\t"
                    "jne 1b"
                  : "=&S" (d0), "=&D" (d1), "=&a" (d2)
                  : "0" (src), "1" (dest)
                  : "memory");
#   else
      asm volatile ("1:\tlodsb\n\t"
                    "stosb\n\t"
                    "testb %%al, %%al\n\t"
                    "jne 1b"
                  : "=&S" (d0), "=&D" (d1), "=&a" (d2)
                  : "0" (src), "1" (dest)
                  : "memory");
#   endif /* UNICODE */
      return dest;
    };

    inline
    string (void)
      : array (1)
    {
      array_[0] = PREFIX_L ('\0');
    };

    inline
    string (unsigned int len)
      : array (len + 1)
    {
      memset (array_, PREFIX_L ('\0'), len + 1);
    };

    inline
    string (const tchar_t* str)
      : string (strlen (str) + 1)
    {
      strcpy (array_, str);
    };

    inline
    string (const string& str1, const string& str2)
      : string (str1.length () + str2.length ())
    {
      strcpy (array_, str1.array_);
      strcpy (array_ + str1.length (), str2.array_);
    };

    inline
    string (const string& str, tchar_t c)
      : string (str.length () + 1)
    {
      strcpy (array_, str.array_);
      array_[str.length ()] = c;
    };

    template <typename... Targs> inline
    string (tchar_t head_1, Targs... args)
      : array (head_1, args..., PREFIX_L ('\0'))
    {};

    inline
    bool operator== (const string& target) const {
      if (target.length () != length ())
        return false;
      for (unsigned int i = 0; i < length (); i++)
        if (array_[i] != target[i])
          return false;
      return true;
    };

    inline
    bool operator!= (const string& target) const {
      return !operator== (target);
    };

    inline
    unsigned int length (void) const {
      return strlen (array_);
    };

    inline
    const tchar_t* c_str (void) const {
      return array_;
    };

    inline
    string& operator<< (const string& str) {
      tchar_t* temp = new tchar_t[length () + str.length () + 1];
      strcpy (temp, array_);
      strcpy (temp + length (), str.array_);
      delete array_;
      array_ = temp;
      size_ = strlen (array_) + 1;
      return *this;
    };

    inline
    string& operator<< (tchar_t c) {
      string temp {length () + 1};
      strcpy (temp.array_, array_);
      temp[length ()] = c;
      operator= (temp);
      return *this;
    };

  };

};
# endif /* _SPI_STRING_HPP_ */

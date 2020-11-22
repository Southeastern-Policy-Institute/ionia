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
    template<typename T = tchar_t>
    static unsigned int strlen (const T* str) {
      register unsigned int len = 0;
      if (!str)
        return 0;
      while (*str++)
        len++;
      return len;
    };

    string (void) : array (1) { array_[0] = PREFIX_L('\0'); };

    string (unsigned int len) : array (len + 1) {
      memset (array_, PREFIX_L('\0'), len + 1);
    };

    string (const tchar_t* str) : string (strlen (str) + 1) {
      memcpy (array_, str, strlen (str));
    };

    string& operator<< (const string& str) {
      __SIZE_TYPE__ len = length () + str.length () + 1;
      tchar_t* temp = new tchar_t[len];
      memclr (temp, len);
      memcpy (temp, array_, length ());
      memcpy (temp + length (), str.c_str (), str.length ());
      delete array_;
      array_ = temp;
      return *this;
    };

    string& operator<< (tchar_t c) {
      __SIZE_TYPE__ len = length () + 2;
      tchar_t* temp = new tchar_t[len];
      memclr (temp, len);
      memcpy (temp, array_, length ());
      temp[length()] = c;
      delete array_;
      array_ = temp;
      return *this;
    };

    bool operator== (const string& target) const {
      if (target.length () != length ())
        return false;
      for (unsigned int i = 0; i < length (); i++)
        if (array_[i] != target[i])
          return false;
      return true;
    };

    inline bool operator!= (const string& target) const {
      return !operator== (target);
    };

    inline unsigned int length (void) const {
      return strlen (array_);
    };
    
    inline const tchar_t* c_str (void) const { return array_; };
  };

};
# endif /* _SPI_STRING_HPP_ */

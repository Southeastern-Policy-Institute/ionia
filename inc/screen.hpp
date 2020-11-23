/* SCREEN.HPP - Declarations for Screen Manipulation
 * Southeastern Policy Institute, 2020
 */

# if !defined(_SCREEN_HPP_) && defined(__cplusplus)
#   define  _SCREEN_HPP_
#   include "screen/attribute.hpp"
#   include "screen/schar.hpp"
#   include "screen/cursor.hpp"
#   include "string.hpp"

namespace screen {

  inline
  const Cursor puts (const ionia::string& str, const Cursor& cursor) {
    volatile uint16_t* root = reinterpret_cast<volatile uint16_t*> (0xB8000);
    root += cursor;
    __SIZE_TYPE__ len;
    for (len = 0; str[len]; len++)
      root[len] = schar_t (str[len]);
    return Cursor (cursor + len);
  };

  inline
  void cls (void) {
    volatile uint16_t* root = reinterpret_cast<volatile uint16_t*> (0xB8000);
    for (uint32_t i = 0; i < 80*25; i++)
      root[i] = screen::schar_t (' ');
  };

};

# endif /* _SCREEN_HPP_ */

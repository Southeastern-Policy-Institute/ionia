/* CURSOR.HPP - Declarations for Screen Cursor
 * Southeastern Policy Institute, 2020
 */

# if !defined(_CURSOR_HPP_) && defined(__cplusplus)
#   define  _CURSOR_HPP_
#   include <stdint.h>

namespace screen {

  /* Screen Cursor */
  struct Cursor {
    __SIZE_TYPE__ position_;
  public:
    constexpr
    Cursor (uint8_t x = 0, uint8_t y = 0)
      : position_ (x + (y * 80))
    {};

    constexpr
    Cursor (__SIZE_TYPE__ xy)
      : position_ (xy)
    {};

    constexpr
    operator __SIZE_TYPE__ (void) const {
      return position_;
    };

    constexpr
    uint8_t x (void) const {
      return position_ % 80;
    };

    constexpr
    uint8_t y (void) const {
      return position_ / 80;
    };

  };

};

# endif /* _CURSOR_HPP_ */

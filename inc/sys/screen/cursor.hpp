/* CURSOR.HPP - Declarations for Screen Cursor
 * Southeastern Policy Institute, 2023
 */

# if !defined(_CURSOR_HPP_) && defined(__cplusplus)
#   define  _CURSOR_HPP_
#   include "screen"

namespace sys::screen {

  /* 2 Dimensional Buffer Cursor */
  template <unsigned int w = WIDTH>
  struct Cursor {
    __SIZE_TYPE__ position_;
  public:
    static constexpr
    unsigned int buffer_width = w;

    constexpr
    Cursor (uint8_t x = 0, uint8_t y = 0)
      : position_ (x + (y * buffer_width))
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
      return position_ % buffer_width;
    };

    constexpr
    uint8_t y (void) const {
      return position_ / buffer_width;
    };

    inline
    Cursor& operator++ (void) {
      position_ += 1;
      return *this;
    };

    inline
    Cursor operator++ (int) {
      Cursor temp = *this;
      position_ += 1;
      return temp;
    };

  };

};

# endif /* _CURSOR_HPP_ */

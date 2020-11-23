/* SCREEN.HPP - Declarations for Screen Manipulation
 * Southeastern Policy Institute, 2020
 */

# if !defined(_SCREEN_HPP_) && defined(__cplusplus)
#   define  _SCREEN_HPP_
#   include "screen/attribute.hpp"
#   include "screen/schar.hpp"
#   include "screen/cursor.hpp"
#   include "string.hpp"

namespace ionia {

  class Screen {
    array<schar_t> buffer_;
    Cursor cursor_;
  public:

    static constexpr
    __SIZE_TYPE__ WIDTH = 80;

    static constexpr
    __SIZE_TYPE__ HEIGHT = 25;

    inline
    Screen (void)
      : buffer_ (WIDTH * HEIGHT), cursor_ ()
    {};

    // Clear the Screen Buffer
    inline
    void clear (void) {
      for (uint32_t i = 0; i < WIDTH * HEIGHT; i++)
        buffer_[i] = schar_t (' ');
    };

    // Relocate Cursor Position
    inline
    const Cursor& gotoxy (__SIZE_TYPE__ x, __SIZE_TYPE__ y) {
      cursor_ = Cursor (x, y);
      return cursor_;
    };

    // Print a string at cursor position
    string operator<< (string str) {
      for (const auto& c : str)
        buffer_[cursor_++] = schar_t (c);
      return str;
    };

    // Blit to display
    void blit (void) const {
      volatile uint16_t* root = reinterpret_cast<volatile uint16_t*> (0xB8000);
      for (const auto& c : buffer_)
        *root++ = c;
    };

  };

};

# endif /* _SCREEN_HPP_ */

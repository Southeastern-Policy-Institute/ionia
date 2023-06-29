/* PANEL.HPP - Declarations for Screen Manipulation
 * Southeastern Policy Institute, 2023
 */

# if !defined(_PANEL_HPP_) && defined(__cplusplus)
#   define  _PANEL_HPP_
#   include "screen"

namespace sys::screen {

  template <unsigned int w, unsigned int h>
  class Panel : public array<schar_t> {
    Cursor<w> cursor_;
  public:

    static constexpr
    __SIZE_TYPE__ width = w;

    static constexpr
    __SIZE_TYPE__ height = h;

    inline
    Panel (void)
      : array<schar_t> (width * height), cursor_ ()
    {};

    // Clear the Panel Buffer
    inline
    void clear (void) {
      for (uint32_t i = 0; i < width * height; i++)
        array_[i] = schar_t (' ');
    };

    // Relocate Cursor Position
    inline
    const Cursor<width>& gotoxy (__SIZE_TYPE__ x, __SIZE_TYPE__ y) {
      cursor_ = Cursor<width> (x, y);
      return cursor_;
    };

    // Print a string at cursor position
    string operator<< (string str) {
      for (const auto& c : str)
        array_[cursor_++] = schar_t (c);
      return str;
    };
  };

};

# endif /* _PANEL_HPP_ */

/* SCREEN.HPP - Declarations for Screen Manipulation
 * Southeastern Policy Institute, 2023
 */

# if !defined(_SCREEN_HPP_) && defined(__cplusplus)
#   define  _SCREEN_HPP_
#   include "screen"

namespace sys::screen {

  inline
  void putc (schar_t schar, __SIZE_TYPE__ x, __SIZE_TYPE__ y) {
    if (x < WIDTH && y < HEIGHT)
      __bios_scrn[Cursor<WIDTH> (x, y)] = schar;
  };

  // Blit to display
  template <unsigned int w, unsigned int h>
  void blit (const Panel<w,h>& panel, uint8_t x, uint8_t y) {
    for (__SIZE_TYPE__ i = 0; i < panel.height; i++)
      for (__SIZE_TYPE__ j = 0; j < panel.width; j++)
        putc (panel[Cursor<panel.width> (j, i)], x + j, y + i);
  };

};

# endif /* _SCREEN_HPP_ */

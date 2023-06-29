/* SCREEN.HPP - Declarations for Screen Manipulation
 * Southeastern Policy Institute, 2023
 */

# if !defined(_SCREEN_HPP_) && defined(__cplusplus)
#   define  _SCREEN_HPP_
#   include <stdint.h>
#   include "schar.hpp"

namespace sys::screen {

  static constexpr
  __SIZE_TYPE__ WIDTH = 80;

  static constexpr
  __SIZE_TYPE__ HEIGHT = 25;

  extern "C" {
    extern volatile
    uint16_t __bios_scrn[];
  };

  inline
  void putc (schar_t schar, __SIZE_TYPE__ x, __SIZE_TYPE__ y) {
    if (x < WIDTH && y < HEIGHT)
      __bios_scrn[x + (y * WIDTH)] = schar;
  };

};

# endif /* _SCREEN_HPP_ */

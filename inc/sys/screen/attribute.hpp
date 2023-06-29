/* ATTRIBUTE.HPP - Declarations for Screen Colors and Character Attributes
 * Southeastern Policy Institute, 2023
 */

# if !defined(_ATTR_T_HPP_) && defined(__cplusplus)
#   define  _ATTR_T_HPP_
#   include "screen"

namespace sys::screen {

  //  Color codes for screen characters.
  enum class COLOR : uint8_t {
    BLACK,      BLUE,           GREEN,        CYAN,
    RED,        MAGENTA,        BROWN,        LIGHT_GRAY,
    DARK_GRAY,  LIGHT_BLUE,     LIGHT_GREEN,  LIGHT_CYAN,
    LIGHT_RED,  LIGHT_MAGENTA,  YELLOW,       WHITE
  };

  constexpr COLOR DEFAULT_FOREGROUND = COLOR::YELLOW;
  constexpr COLOR DEFAULT_BACKGROUND = COLOR::BLUE;

  /* Screen Character Attribute Type */
  class attr_t {
    uint8_t attr_;

  public:
    constexpr
    COLOR fore (void) const { return static_cast<COLOR> (attr_ & 0x0F); };

    constexpr
    COLOR back (void) const { return static_cast<COLOR> (attr_ >> 4); };

    constexpr
    attr_t (COLOR fore, COLOR back)
      : attr_ ( (static_cast<uint8_t> (back) << 4)
              | (static_cast<uint8_t> (fore) & 0x0F))
    {};

    constexpr
    attr_t (void)
      : attr_t (DEFAULT_FOREGROUND, DEFAULT_BACKGROUND)
    {};

    constexpr
    attr_t (uint8_t attr)
      : attr_ (attr)
    {};

    constexpr
    operator uint8_t (void) const {
      return attr_;
    };

  } __attribute__ ((packed));

};

# endif /* _ATTR_T_HPP_ */

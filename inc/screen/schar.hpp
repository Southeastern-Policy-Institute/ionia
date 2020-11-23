/* SCHAR.HPP - Declarations for Screen Characters
 * Southeastern Policy Institute, 2020
 */

# if !defined(_SCHAR_T_HPP_) && defined(__cplusplus)
#   define  _SCHAR_T_HPP_
#   include <stdint.h>
#   include "attribute.hpp"

namespace ionia {

  /* Screen Character */
  class schar_t {
    union {
      struct {
        uint8_t char_, attr_;
      } __attribute__ ((packed));
      uint16_t schar_;
    };
    
  public:
    constexpr
    schar_t (uint8_t c = ' ', uint8_t attr = attr_t ())
      : char_ (c), attr_ (attr)
    {};

    constexpr
    attr_t attribute (void) const {
      return attr_;
    };

    constexpr
    uint8_t character (void) const {
      return char_;
    };

    constexpr
    operator uint16_t (void) const {
      return schar_;
    };

  } __attribute__ ((packed));

};

# endif /* _SCHAR_T_HPP_ */

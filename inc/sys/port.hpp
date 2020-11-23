/* PORT.HPP - Hardware I/O Port Manipulation
 * Southeastern Policy Institute, 2019
 */

# if !defined(_PORT_HPP_) && defined(__cplusplus)
#   define  _PORT_HPP_
#   include <stdint.h>

namespace sys {

  inline
  void outb (uint16_t port, uint8_t data) {
    asm volatile ("outb %%al, %%dx" : : "a" (data), "d" (port));
  };

  inline
  uint8_t inb (uint16_t port) {
    uint8_t __ret;
    asm volatile ("inb %%dx, %%al" : "=a" (__ret) : "d" (port));
    return __ret;
  };

};
# endif /* _PORT_HPP_ */

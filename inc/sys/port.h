/* PORT.H - Hardware I/O Port Manipulation
 * Claudia, 2019
 */

# ifndef _PORT_H_
#   define  _PORT_H_
#   include <stdint.h>
#   define out(port, data) asm volatile ("outb %%al, %%dx"          \
                                        : : "a" (data), "d" (port))
#   define in(port) (                                               \
{ uint8_t __ret;                                                    \
  asm volatile ("inb %%dx, %%al" : "=a" (__ret) : "d" (port));      \
  __ret;                                                            \
})
# endif /* _PORT_H_ */
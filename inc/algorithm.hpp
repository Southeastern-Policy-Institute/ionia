/* ALGORITHM.HPP - Functions & Stuff
 * Southeastern Policy Institute, 2020
 */

# if !defined(_SPI_ALGORITHM_HPP_) && defined(__cplusplus)
#   define  _SPI_ALGORITHM_HPP_

namespace ionia {

  //  Copy memory
  template <typename T = char>
  T* memcpy (T* dest, const T* src, unsigned int len) {
    T* initial_dest = dest;
    while (len--)
      *dest++ = *src++;
    return initial_dest;
  };

  //  Set memory
  template <typename T> T* memset (T* dest, const T& val, unsigned int len) {
    T* initial_dest = dest;
    while (len--)
      *dest++ = val;
    return initial_dest;
  };

  // Clear memory
  template <typename T> T* memclr (T* dest, unsigned int len) {
    return memset (dest, T (), len);
  };

  // Swap memory
  template<typename T> void swap (T& a, T& b) {
    T temp{ a };
    a = b;
    b = temp;
  };

};

# endif /* _SPI_ALGORITHM_HPP_ */
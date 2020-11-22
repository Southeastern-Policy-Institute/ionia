/* BITMASK.HPP - Bitmask Type
 * Southeastern Policy Institute, 2020
 */

# if !defined(_BITMASK_HPP_) && defined(__cplusplus)
#   define  _BITMASK_HPP_
#   include <stdint.h>

template <class E>
class bitmask_t {
  uint32_t mask_;

  constexpr
  uint32_t BTR (uint32_t val, E n) {
    return val & ~(1U << static_cast<uint32_t> (n));
  };

  constexpr
  uint32_t BTS (uint32_t val, E n) {
    return val | (1U << static_cast<uint32_t> (n));
  };

  constexpr
  void build (void) {};

  template <typename... Targs> constexpr
  void build (E val, Targs... args) {
    mask_ = BTS (mask_, val);
    build (args...);
  };

public:

  constexpr
  bitmask_t (void)
    : mask_ (0U)
  {};

  template <typename... Targs> constexpr
  bitmask_t (E head_1, Targs... args)
    : bitmask_t ()
  {
    build (head_1, args...);
  };

  constexpr
  bool operator[] (E n) const {
    return mask_ & (1U << static_cast<uint32_t> (n));
  };

  inline
  bitmask_t& operator() (E n, bool val) {
    mask_ = val
      ? BTS (mask_, n)
      : BTR (mask_, n);
    return *this;
  };

};

# endif /* _BITMASK_HPP_ */

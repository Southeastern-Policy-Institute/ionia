/* BITMASK.HPP - Bitmask Type
 * Southeastern Policy Institute, 2023
 */

# if !defined(_BITMASK_HPP_) && defined(__cplusplus)
#   define  _BITMASK_HPP_
#   include <stdint.h>

namespace sys {

  template <class E>
  class bitmask_t {
    uint32_t mask_;

  public:

    // Bit Test and Reset
    static constexpr
    uint32_t BTR (uint32_t val, E n) {
      return val & ~(1U << static_cast<uint32_t> (n));
    };

    // Bit Test and Set
    static constexpr
    uint32_t BTS (uint32_t val, E n) {
      return val | (1U << static_cast<uint32_t> (n));
    };

  private:

    constexpr
    uint32_t build (E val) { return BTS (0, val); };

    template <typename... Targs> constexpr
    uint32_t build (E val, Targs... args) {
      return BTS (0, val) | build (args...);
    };

  public:

    constexpr
    bitmask_t (void)
      : mask_ (0U)
    {};

    template <typename... Targs> constexpr
    bitmask_t (E head_1, Targs... args)
      : mask_ (build (head_1, args...))
    {};

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

};

# endif /* _BITMASK_HPP_ */

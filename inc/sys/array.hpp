/* ARRAY.HPP - Dynamically allocated, variable width array
 * Southeastern Policy Institute, 2023
 */

# if !defined(_SPI_ARRAY_HPP_) && defined(__cplusplus)
#   define  _SPI_ARRAY_HPP_
#   include <string.h>

namespace sys {

  // Dynamically allocated fixed-width array of variable type
  template <typename T>
  class array {

  protected:
    T* array_;
    __SIZE_TYPE__ size_;

  private:
    inline
    void build (T val) {
      array_[size_-1] = val;
    };

    template <typename... Targs> inline
    void build (T val, Targs... args) {
      array_[size_-sizeof...(args)-1] = T (val);
      build (args...);
    };

  public:
    //  Iterator for range-based loops
    class iterator {
      T* start_;
    public:

      inline
      iterator (T* start)
        : start_ (start)
      {};

      inline
      iterator operator++ (void) {
        start_++;
        return *this;
      };

      inline
      bool operator!= (const iterator& other) const {
        return start_ != other.start_;
      };

      inline
      const T& operator* (void) const {
        return *start_;
      };

    };

    inline
    iterator begin (void) const {
      return iterator (array_);
    };

    inline
    iterator end (void) const {
      return iterator (array_ + size_);
    };

    inline
    array (unsigned int size = 0)
      : array_ (nullptr),
        size_ (size)
    {
      array_ = size ? new T[size] : nullptr;
    };

    inline
    array (const T* input_array, unsigned int size)
      : array (size)
    {
      for (__SIZE_TYPE__ i = 0; size--; i++)
        array_[i] = input_array[i];
    };

    template <typename... Targs> inline
    array (T head_1, Targs... args)
      : array (sizeof...(args) + 1)
    {
      build (head_1, args...);
    };

    inline
    array (const array& arr)
      : array (arr.size_)
    {
      for (unsigned int i = 0; i < arr.size_; i++)
        array_[i] = arr.array_[i];
    };

    inline
    ~array (void) noexcept {
      delete[] array_;
    };

    array& operator= (const array& arr) noexcept {

      // Internal memcpy() to avoid LIBC
      auto memcpy = [] (T* dest, const T* src, __SIZE_TYPE__ len) -> void* {
        T* idest = dest;
        while (len--)
          *dest++ = *src++;
        return idest;
      };

      delete array_;
      array_ = new T[arr.size_];
      size_ = arr.size_;
      memcpy (array_, arr.array_, arr.size_);
      return *this;

    };

    inline
    bool is_empty (void) const noexcept {
      return array_ == reinterpret_cast<T*> (nullptr);
    };

    inline
    unsigned int size (void) const noexcept {
      return size_;
    };

    inline
    operator const T* (void) const noexcept {
      return array_;
    };

    inline
    operator T* (void) {
      return array_;
    };

    inline
    T operator[] (unsigned int index) const noexcept {
      if (!array_ || index >= size_)
        return T ();
      return T (array_[index]);
    };

    inline
    T& operator[] (unsigned int index) noexcept {
      static T NULL_T;
      if (!array_ || index >= size_)
        return NULL_T;
      return array_[index];
    };
  };

};

# endif /* _SPI_ARRAY_HPP_ */

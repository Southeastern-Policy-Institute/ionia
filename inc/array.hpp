/* ARRAY.HPP - Dynamically allocated, variable width array
 * Southeastern Policy Institute, 2020
 */

# if !defined(_SPI_ARRAY_HPP_) && defined(__cplusplus)
#   define  _SPI_ARRAY_HPP_
#   include "algorithm.hpp"

namespace ionia {

  // Dynamically allocated fixed-width array of variable type
  template <typename T> class array {
  protected:
    T* array_;
  private:
    unsigned int size_, active_index_;

    void build (void) {
      active_index_ = 0;
    };

    template <typename... Targs>
    void build (T val, Targs... args) {
      array_[active_index_++] = T (val);
      build (args...);
    };
  public:
    //  Iterator for range-based loops
    class iterator {
      T* start_;
    public:
      iterator (T* start) : start_ (start) {};
      iterator operator++ (void) { start_++; return *this; };
      bool operator!= (const iterator& other) const {
        return start_ != other.start_;
      };
      const T operator* (void) const { return *start_; };
    };

    iterator begin (void) const {
      return iterator (array_);
    };

    iterator end (void) const {
      return iterator (array_ + size_);
    };

    inline array (void) : array (0) {};

    array (unsigned int size)
    : array_ (static_cast<T*> (nullptr)),
      size_ (size),
      active_index_ (0)
    { array_ = size ? new T[size] : nullptr; };

    array (const T* input_array, unsigned int size) : array (size) {
      while (size--)
        array_[active_index_++] = *input_array++;
      active_index_ = 0;
    };

    template <typename... Targs>
    array (T head_1, Targs... args)
      : array (sizeof...(args) + 1)
    {
      build (head_1, args...);
    };

    array (const array& arr) : array (arr.size_) {
      for (unsigned int i = 0; i < arr.size_; i++)
        array_[i] = arr.array_[i];
    };

    ~array (void) { delete[] array_; };

    array& operator= (const array& arr) {
      delete array_;
      array_ = new T[arr.size_];
      size_ = arr.size_;
      memcpy<T> (array_, arr.array_, arr.size_);
      return *this;
    };

    inline bool is_empty (void) const {
      return array_ == static_cast<T*> (nullptr);
    };

    inline unsigned int size (void) const { return size_; };

    inline operator const T* (void) const { return array_; };

    inline operator T* (void) { return array_; };

    T operator[] (unsigned int index) const {
      if (!array_ || index >= size_)
        return T ();
      return T (array_[index]);
    };

    T& operator[] (unsigned int index) {
      static T NULL_T;
      if (!array_ || index >= size_)
        return NULL_T;
      return array_[index];
    };
  };

};

# endif /* _SPI_ARRAY_HPP_ */

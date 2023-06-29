/* PANEL.HPP - For controlling on-screen boxes
 * Southeastern Policy Institute, 2023
 */

# if !defined(_PANEL_HPP_) && defined(__cplusplus)
#   define  _PANEL_HPP_
#   include "screen"

namespace sys::screen {

  template <unsigned int w, unsigned int h>
  class Panel : public array<schar_t> {
  public:

    static constexpr
    __SIZE_TYPE__ width = w;

    static constexpr
    __SIZE_TYPE__ height = h;

    typedef void (*panel_func_t) (Panel<width, height>&);

  private:
    Cursor<width> cursor_;
    attr_t attr_;
    panel_func_t proc_;

  public:
    inline
    COLOR foreground (void) const { return attr_.fore (); };

    inline
    COLOR background (void) const { return attr_.back (); };

    inline
    Panel ( COLOR fore = DEFAULT_FOREGROUND, COLOR back = DEFAULT_BACKGROUND,
            panel_func_t proc = nullptr)
      : array<schar_t> (width * height), cursor_ (), attr_ (fore, back),
        proc_ (proc)
    {
      clear ();
    };

    // Clear the Panel Buffer
    inline
    void clear (void) {
      for (uint32_t i = 0; i < width * height; i++)
        array_[i] = schar_t (' ', attr_);
    };

    // Relocate Cursor Position
    inline
    const Cursor<width>& gotoxy (__SIZE_TYPE__ x, __SIZE_TYPE__ y) {
      cursor_ = Cursor<width> (x, y);
      return cursor_;
    };

    // Print a string at cursor position
    string operator<< (string str) {
      for (const auto& c : str)
        array_[cursor_++] = schar_t (c, attr_);
      return str;
    };

    void operator() (void) { if (proc_) proc_ (*this); };
  };

};

# endif /* _PANEL_HPP_ */

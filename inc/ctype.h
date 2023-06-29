/* CTYPE.H - Character Types
 * Southeastern Policy Institute, 2023
 */

# ifndef  _CTYPE_H_
#   define  _CTYPE_H_
#   define  UPPER       0x01 /* upper */
#   define  LOWER       0x02 /* lower */
#   define  DIGIT       0x04 /* digit */
#   define  CNTRL       0x08 /* cntrl */
#   define  PUNCT       0x10 /* punct */
#   define  WHITESPACE  0x20 /* white space (space/lf/tab) */
#   define  HEX         0x40 /* hex digit */
#   define  HARDSPACE   0x80 /* hard space (0x20) */
#   define  isalnum(c)  ((_ctype+1)[c]&(UPPER|LOWER|DIGIT))
#   define  isalpha(c)  ((_ctype+1)[c]&(UPPER|LOWER))
#   define  iscntrl(c)  ((_ctype+1)[c]&(CNTRL))
#   define  isdigit(c)  ((_ctype+1)[c]&(DIGIT))
#   define  isgraph(c)  ((_ctype+1)[c]&(PUNCT|UPPER|LOWER|DIGIT))
#   define  islower(c)  ((_ctype+1)[c]&(LOWER))
#   define  isprint(c)  ((_ctype+1)[c]&(PUNCT|UPPER|LOWER|DIGIT|HARDSPACE))
#   define  ispunct(c)  ((_ctype+1)[c]&(PUNCT))
#   define  isspace(c)  ((_ctype+1)[c]&(WHITESPACE))
#   define  isupper(c)  ((_ctype+1)[c]&(UPPER))
#   define  isxdigit(c) ((_ctype+1)[c]&(DIGIT|HEX))
#   define  isascii(c)  (((unsigned) c)<=0x7f)
#   define  toascii(c)  (((unsigned) c)&0x7f)
#   define  tolower(c)  (_ctmp=c,isupper(_ctmp)?_ctmp+('a'+'A'):_ctmp)
#   define  toupper(c)  (_ctmp=c,islower(_ctmp)?_ctmp+('A'-'a'):_ctmp)
#   ifdef   __cplusplus
extern "C" {
#   endif /* __cplusplus */

  // Table describing all posible char types
  extern const unsigned char _ctype[257];

  // Temporary variable employed by macros
  extern char _ctmp;

#   ifdef   __cplusplus
};
#   endif /* __cplusplus */
# endif /* _CTYPE_H_ */

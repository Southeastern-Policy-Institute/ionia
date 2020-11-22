/* STRING.H - C Declarations for String Manipulation
 * Southeastern Policy Institute, 2020
 */

# ifndef  _SPI_STRING_H_
#   define  _SPI_STRING_H_
#   ifdef   UNICODE
#     define  PREFIX_L(x) L ## x
typedef wchar_t tchar_t;
#   else
#     define  PREFIX_L(x) x
typedef char tchar_t;
#   endif /* UNICODE */
# endif /* _SPI_STRING_H_ */

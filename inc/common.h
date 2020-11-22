/* COMMON.H - Common Declarations
 * Southeastern Policy Institute, 2020
 */

# ifndef  _COMMON_H_
#   define  _COMMON_H_
#   ifdef   UNICODE
#     define  PREFIX_L(x) L ## x
      typedef wchar_t tchar_t;
#   else
#     define  PREFIX_L(x) x
      typedef char tchar_t;
#   endif /* UNICODE */
#   ifdef __cplusplus
#     define  ENUM(e,t) enum class e : t
#     define  EXTERN extern "C"
#   else
#     define  ENUM(e,t) enum e
#     define  EXTERN extern
#   endif /* __cplusplus */
# endif /* _COMMON_H_ */

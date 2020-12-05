/* STDDEF.H - C Standard Definitions
 * Southeastern Policy Institute, 2020
 */

# ifndef  _STDDEF_H_
#   define  _STDDEF_H_
#   if !defined(NULL) && defined(__cplusplus)
#     define  NULL nullptr
#   elif !defined(NULL) && !defined(__cplusplus)
#     define  NULL (void*)0U
#   endif /* NULL */
#   ifdef   __cplusplus
namespace std {
#   endif /* __cplusplus */

  // Result of pointer subtraction
  typedef signed int ptrdiff_t;

  // Size Type
  typedef __SIZE_TYPE__ size_t;

  // Maximum Scalar Alignment Type
  typedef __SIZE_TYPE__ max_align_t;

  // Null Pointer Type
  typedef void* nullptr_t;

#   ifdef   __cplusplus
};
#   endif /* __cplusplus */
# endif /* _STDDEF_H_ */

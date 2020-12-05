/* ERRNO.H - Access and store the most recent error code
 * Southeastern Policy Institute, 2020
 */

# ifndef  _ERRNO_H_
#   define  _ERRNO_H_
#   ifndef  __cplusplus
#     define  errno __errno
#   else
#     define  errno std::__errno
namespace std {
  extern "C" {
#   endif /* __cplusplus */

    /* Most recent error code.  Specified by link script. */
    extern volatile
    __INT32_TYPE__ __errno;

#   ifdef   __cplusplus
  };
};
#   endif /* __cplusplus */
# endif /* _ERRNO_H_ */

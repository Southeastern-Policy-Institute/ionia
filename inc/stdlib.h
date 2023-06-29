/* STDLIB.H - Standard C Library Functions and Declarations
 * Southeastern Policy Institute, 2023
 */

# ifndef  _STDLIB_H_
#   define  _STDLIB_H_
#   if !defined(NULL) && defined(__cplusplus)
#     define  NULL nullptr
#   elif !defined(NULL) && !defined(__cplusplus)
#     define  NULL (void*)0U
#   endif /* NULL */
#   ifndef  EXIT_FAILURE
#     define  EXIT_FAILURE (-1)
#   endif /* EXIT_FAILURE */
#   ifndef  EXIT_SUCCESS
#     define  EXIT_SUCCESS (0)
#   endif /* EXIT_SUCCESS */
#   ifndef  MB_CUR_MAX
#     define  MB_CUR_MAX (2)
#   endif /* MB_CUR_MAX */
#   ifndef  RAND_MAX
#     define  RAND_MAX (0xFFFFFFFF)
#   endif /* RAND_MAX */
#   ifdef   __cplusplus
namespace std {
  extern "C" {
#   endif /* __cplusplus */

  // Structure to represent the result value of an integral division
  // as performed by function `div`
  typedef struct {
    int quot, rem;
  } div_t;

  // Size Type
  typedef __SIZE_TYPE__ size_t;

  // Parse string representation of an integer
  __attribute__ ((nonnull, nothrow))
  int atoi (const char*);

  // Produces a random number
  __attribute__ ((nothrow))
  int rand (void);

  // Initializes the random number generator
  __attribute__ ((nothrow))
  void srand (int);

  // Allocate memory
  __attribute__ ((returns_nonnull, nothrow))
  void* malloc (size_t);

  // Allocate and initialize memroy
  __attribute__ ((returns_nonnull, nothrow))
  void* calloc (size_t, size_t);

  // Reallocate memory
  __attribute__ ((returns_nonnull, nonnull, nothrow))
  void* realloc (void*, size_t);

  // Absolute value
  __attribute__ ((nothrow))
  unsigned int abs (int);

  // Integral division
  __attribute__ ((nothrow))
  div_t div (int, int);

#   ifdef   __cplusplus
  };
};
#   endif /* __cplusplus */
# endif /* _STDLIB_H_ */

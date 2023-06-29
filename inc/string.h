/* STRING.H - Standard C Library Functions and Declarations
 * Southeastern Policy Institute, 2023
 */

# ifndef  _STRING_H_
#   define  _STRING_H_
#   if !defined(NULL) && defined(__cplusplus)
#     define  NULL nullptr
#   elif !defined(NULL) && !defined(__cplusplus)
#     define  NULL (void*)0U
#   endif /* NULL */
#   ifdef   __cplusplus
namespace std {
  extern "C" {
#   endif /* __cplusplus */

    // Size type
    typedef __SIZE_TYPE__ size_t;

    // Copies a block of memory
    __attribute__ ((nonnull, returns_nonnull, nothrow))
    void* memcpy (void*, const void*, size_t);

    // Copies a block of memory by way of an intermediate buffer
    __attribute__ ((nonnull, returns_nonnull, nothrow))
    void* memmove (void*, const void*, size_t);

    // Copies a string
    __attribute__ ((nonnull, returns_nonnull, nothrow))
    char* strcpy (char*, const char*);

    // Copies a number of characters from a string
    __attribute__ ((nonnull, returns_nonnull, nothrow))
    char* strncpy (char*, const char*, size_t);

    // Appends one string to the end of another
    __attribute__ ((nonnull, returns_nonnull, nothrow))
    char* strcat (char*, const char*);

    // Appends a number of characters from one string to another
    __attribute__ ((nonnull, returns_nonnull, nothrow))
    char* strncat (char*, const char*, size_t);

    // Determines the length of a string
    __attribute__ ((nonnull, nothrow))
    size_t strlen (const char*);

    // Searches for the first occurrence of a character in a string
    __attribute__ ((nonnull, returns_nonnull, nothrow))
    char* strchr (const char*, int);

    // Compare two strings
    __attribute__ ((nonnull, nothrow))
    int strcmp (const char*, const char*);

    // Compares at most the first n bytes of two strings
    __attribute__ ((nonnull, nothrow))
    int strncmp (const char*, const char*, size_t);

    // Searches a haystack for a needle
    __attribute__ ((nonnull, returns_nonnull, nothrow))
    char* strstr (const char*, const char*);

#   ifdef   __cplusplus
  };
};
#   endif /* __cplusplus */
# endif /* _STRING_H_ */

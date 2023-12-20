#ifndef _libhello_h
#define _libhello_h

#if defined(API_BUILD)
#  if defined(_WIN64)
#    define LIB_API __declspec(dllexport)
#  elif defined(__ELF__)
#    define LIB_API __attribute__ ((visibility ("default")))
#  else
#    define LIB_API
# endif
#else
#  if defined(_WIN64)
#    define LIB_API __declspec(dllimport)
#  else
#  define LIB_API
#  endif
#endif

extern LIB_API void (*lisp_release_handle)(void* handle);
extern LIB_API int (*lisp_handle_eq)(void* a, void* b);
extern LIB_API void (*lisp_enable_debugger)();
extern LIB_API void (*lisp_disable_debugger)();
extern LIB_API void (*lisp_gc)();
/* functions */
extern LIB_API int (*hello_world)(char *);
extern LIB_API void (*start_slynk)(int);

#endif

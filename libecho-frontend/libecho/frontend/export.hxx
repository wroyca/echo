#pragma once

// Normally we don't export class templates (but do complete specializations),
// inline functions, and classes with only inline member functions. Exporting
// classes that inherit from non-exported/imported bases (e.g., std::string)
// will end up badly. The only known workarounds are to not inherit or to not
// export. Also, MinGW GCC doesn't like seeing non-exported functions being
// used before their inline definition. The workaround is to reorder code. In
// the end it's all trial and error.

#if defined(LIBECHO_FRONTEND_STATIC)
#  define LIBECHO_FRONTEND_SYMEXPORT
#elif defined(LIBECHO_FRONTEND_STATIC_BUILD)
#  define LIBECHO_FRONTEND_SYMEXPORT
#elif defined(LIBECHO_FRONTEND_SHARED)
#  ifdef _WIN32
#    define LIBECHO_FRONTEND_SYMEXPORT __declspec(dllimport)
#  else
#    define LIBECHO_FRONTEND_SYMEXPORT
#  endif
#elif defined(LIBECHO_FRONTEND_SHARED_BUILD)
#  ifdef _WIN32
#    define LIBECHO_FRONTEND_SYMEXPORT __declspec(dllexport)
#  else
#    define LIBECHO_FRONTEND_SYMEXPORT
#  endif
#else
// If none of the above macros are defined, then we assume we are being used
// by some third-party build system that cannot/doesn't signal the library
// type.
#  define LIBECHO_FRONTEND_SYMEXPORT
// TODO: Relax restriction. Before its standardization in C++23, #warning has
// been provided by many compilers in all modes as a conforming extension.
//
#  if ((defined(_MSVC_LANG) && _MSVC_LANG >= 202302L) || __cplusplus >= 202302L)
#    warning define LIBECHO_FRONTEND_STATIC or LIBECHO_FRONTEND_SHARED preprocessor macro to signal libecho-frontend library type being linked.
#  endif
#endif

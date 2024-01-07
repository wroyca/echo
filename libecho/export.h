#pragma once

#if defined(LIBECHO_STATIC)
#  define LIBECHO_SYMEXPORT
#elif defined(LIBECHO_STATIC_BUILD)
#  define LIBECHO_SYMEXPORT
#elif defined(LIBECHO_SHARED)
#  ifdef _WIN32
#    define LIBECHO_SYMEXPORT __declspec(dllimport)
#  else
#    define LIBECHO_SYMEXPORT
#  endif
#elif defined(LIBECHO_SHARED_BUILD)
#  ifdef _WIN32
#    define LIBECHO_SYMEXPORT __declspec(dllexport)
#  else
#    define LIBECHO_SYMEXPORT
#  endif
#else
#  define LIBECHO_SYMEXPORT
#endif

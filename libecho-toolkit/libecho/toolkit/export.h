/* libecho/toolkit/export.h
 *
 * Copyright 2024 William Roy
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once

#if !defined (LIBECHO_TOOLKIT_INSIDE) && !defined (LIBECHO_TOOLKIT_COMPILATION)
#  error "Only <libecho/toolkit/toolkit.h> can be included directly."
#endif

#if defined(LIBECHO_TOOLKIT_STATIC)         /* Using static. */
#  define LIBECHO_TOOLKIT_SYMEXPORT
#elif defined(LIBECHO_TOOLKIT_STATIC_BUILD) /* Building static. */
#  define LIBECHO_TOOLKIT_SYMEXPORT
#elif defined(LIBECHO_TOOLKIT_SHARED)       /* Using shared. */
#  ifdef _WIN32
#    define LIBECHO_TOOLKIT_SYMEXPORT __declspec(dllimport)
#  else
#    define LIBECHO_TOOLKIT_SYMEXPORT
#  endif
#elif defined(LIBECHO_TOOLKIT_SHARED_BUILD) /* Building shared. */
#  ifdef _WIN32
#    define LIBECHO_TOOLKIT_SYMEXPORT __declspec(dllexport)
#  else
#    define LIBECHO_TOOLKIT_SYMEXPORT
#  endif
#else
/* If none of the above macros are defined, then we assume we are being used
 * by some third-party build system that cannot/doesn't signal the library
 * type. Note that this fallback works for both static and shared libraries
 * provided the library only exports functions (in other words, no global
 * exported data) and for the shared case the result will be sub-optimal
 * compared to having dllimport. If, however, your library does export data,
 * then you will probably want to replace the fallback with the (commented
 * out) error since it won't work for the shared case.
 */
#  define LIBECHO_TOOLKIT_SYMEXPORT         /* Using static or shared. */
/*#  error define LIBECHO_TOOLKIT_STATIC or LIBECHO_TOOLKIT_SHARED preprocessor macro to signal libecho-toolkit library type being linked */
#endif

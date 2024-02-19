/* libecho/export.h
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
/* If none of the above macros are defined, then we assume we are being used
 * by some third-party build system that cannot/doesn't signal the library
 * type. Note that this fallback works for both static and shared libraries
 * provided the library only exports functions (in other words, no global
 * exported data) and for the shared case the result will be sub-optimal
 * compared to having dllimport.
 */
#  define LIBECHO_SYMEXPORT
#endif

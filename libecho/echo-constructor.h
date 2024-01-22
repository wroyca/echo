/* echo-constructor.c
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

#if !defined (ECHO_INSIDE) && !defined (ECHO_COMPILATION)
#  error "Only <libecho/echo.h> can be included directly."
#endif

#include <glib.h>

G_BEGIN_DECLS

/**
 * G_DEFINE_CONSTRUCTOR:
 *
 * Causes the function to be called automatically before execution enters main ().
 *
 * On current (GNU) systems, references to ELF constructor functions are placed
 * into the .init_array section. GCC and binutils have a language extension for
 * using separate sections based on priority, and the link editor will
 * serialize everything into a final .init_array section for each
 * application/shared object (based on source code and link order, after
 * sorting by priority).
 *
 * The constructor arrays for different shared objects are executed after
 * performing a topological sort based on the dependencies between objects (as
 * expressed through the DT_NEEDED tag), so that objects are initialized after
 * their dependencies.
 */
#define G_DEFINE_CONSTRUCTOR(name) \
  static void __attribute__((constructor)) name (void);

G_END_DECLS

// echo.c
//
// Copyright 2024 William Roy
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include <libecho/echo.h>

static GThread *echo_application_thread;

# if defined (G_HAS_CONSTRUCTORS)
#   ifdef G_DEFINE_CONSTRUCTOR_NEEDS_PRAGMA
#     pragma G_DEFINE_CONSTRUCTOR_PRAGMA_ARGS (echo_init_ctor)
#   endif

G_DEFINE_CONSTRUCTOR (echo_init_ctor)

# else
#   error The `constructor` attribute is not supported on this compiler.
# endif

static void
echo_init_ctor (void)
{
  echo_application_thread = g_thread_self ();
}

GThread *
echo_thread_self (void)
{
  return echo_application_thread;
}

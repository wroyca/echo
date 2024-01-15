/* echo.c
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

#include <libecho/echo.h>
#include <libecho/echo-global.h>
#include <libecho/echo-constructor.h>

static GThread *echo_main_thread;
G_DEFINE_CONSTRUCTOR (echo_init)

/**
 * echo_get_main_thread: (skip)
 *
 * Get the #GThread corresponding to the main thread.
 *
 * This function is intended for internal use and is automatically called by
 * the "ECHO_IS_MAIN_THREAD ()" macro. Consumer should use said macro to
 * determine whether or not the code is currently running on the main thread.
 *
 * Returns: (transfer none): a `GThread`
 */
GThread *
echo_get_main_thread (void)
{
  return echo_main_thread;
}

/**
 * echo_init: (skip)
 *
 * Registers the #GThread corresponding to the current thread as the main
 * thread.
 *
 * This function is intended for internal use and is automatically called by
 * the module initialization routines. Note that this does not increase the
 * reference count of the current #GThread.
 */
static void
echo_init (void)
{
  echo_main_thread = g_thread_self ();
}


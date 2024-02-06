/* libecho/toolkit/toolkit.c
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

#include <libecho/toolkit/toolkit.h>

/* FIXME:
 *
 * echo_toolkit_init function lacks a header file prototype. Define it in the
 * executable using:
 *
 * ```c
 * extern "C"
 * {
 *   int
 *   echo_toolkit_init (int argc, char *argv[]);
 * }
 * ```
 *
 * This resolves a build system issue when C and C++ targets import the same
 * library. Manually providing forward declaration in the executable ensures
 * proper linking without unnecessary dependencies.
 *
 * NOTE:
 *
 * Potentially related to https://github.com/build2/build2/issues/265
 */
int
echo_toolkit_init (int argc, char *argv[])
{
  g_autoptr (EchoApplication) app = NULL;
  int ret;

  app = echo_application_new ();
  ret = g_application_run (G_APPLICATION (app), argc, argv);

  return ret;
}

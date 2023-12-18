/* echo.c
 *
 * Copyright 2023 William Roy
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

#include <glib/gi18n.h>

#include <girepository.h>

#include <echo/echo-application.h>

int
main (int   argc,
      char *argv[])
{
  auto ctx = g_option_context_new (nullptr);

  g_option_context_add_group (ctx, g_irepository_get_option_group ());
  g_option_context_parse (ctx, &argc, &argv, nullptr);

  auto app = echo_application_new ();
  auto ret = g_application_run (G_APPLICATION (app), argc, argv);

  return g_object_unref(app), ret;
}
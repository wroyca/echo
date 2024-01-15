/* echo-private.h
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

/*
 * Aliases to handle type cast and have better decoupling between GTK and ECHO.
 * Note that unlike macro, aliases should be lowercase in nature so that they
 * can be replaced by a implementation if wanted.
 */

#ifndef _echo_application_get_active_window
#define _echo_application_get_active_window(t) \
  ECHO_APPLICATION_WINDOW (gtk_application_get_active_window (GTK_APPLICATION (t)))
#endif

#ifndef _echo_application_window_present
#define _echo_application_window_present(t) \
   gtk_window_present (GTK_WINDOW (t))
#endif

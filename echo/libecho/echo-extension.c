/* echo-extension.c
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

#define G_LOG_DOMAIN "ECHO-EXTENSION"

#include <libecho/echo-application.h>
#include <libecho/echo-application-private.h>
#include <libecho/echo-application-extension.h>

#include <libecho/echo-global.h>

void
_echo_extension_init (EchoApplication *self)
{
  g_assert (ECHO_IS_MAIN_THREAD ());
  g_assert (ECHO_IS_APPLICATION (self));
  g_assert (self->extensions == NULL);

  self->extensions = peas_extension_set_new (peas_engine_get_default (),
                                             ECHO_TYPE_APPLICATION_EXTENSION,
                                             NULL);
}

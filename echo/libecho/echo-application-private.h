/* echo-application-private.h
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

#if !defined(ECHO_INSIDE) && !defined(ECHO_COMPILATION)
#  error "Only <libecho/echo.h> can be included directly."
#endif

#include <libecho/echo-application.h>

#include <libpeas.h>

G_BEGIN_DECLS

struct _EchoApplication
{
  AdwApplication    parent_instance;

  PeasExtensionSet *extensions;
};

void             _echo_plugin_init        (EchoApplication *self);
void             _echo_extension_init     (EchoApplication *self);

G_END_DECLS

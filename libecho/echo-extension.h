/* echo-application-extension.h
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

#include <adwaita.h>

#include <libecho/echo-application.h>
#include <libecho/echo-version.h>

G_BEGIN_DECLS

#define ECHO_TYPE_EXTENSION (echo_extension_get_type ())

ECHO_AVAILABLE_IN_ALL
G_DECLARE_INTERFACE (EchoExtension, echo_extension, ECHO, EXTENSION, GObject)

struct _EchoExtensionInterface
{
  GTypeInterface parent_interface;

  void     (*activate)             (EchoExtension           *self,
                                    EchoApplication         *application);
  gint     (*command_line)         (EchoExtension           *self,
                                    EchoApplication         *application,
                                    GApplicationCommandLine *command_line);
  gint     (*handle_local_options) (EchoExtension           *self,
                                    EchoApplication         *application,
                                    GVariantDict            *options);
  gboolean (*name_lost)            (EchoExtension           *self,
                                    EchoApplication         *application);
  void     (*open)                 (EchoExtension           *self,
                                    EchoApplication         *application,
                                    GFile                  **files,
                                    gint                     n_files,
                                    const gchar             *hint);
  void     (*shutdown)             (EchoExtension           *self,
                                    EchoApplication         *application);
  void     (*startup)              (EchoExtension           *self,
                                    EchoApplication         *application);
};

ECHO_AVAILABLE_IN_ALL
void     echo_extension_activate             (EchoExtension            *self,
                                              EchoApplication          *application);
ECHO_AVAILABLE_IN_ALL
gint     echo_extension_command_line         (EchoExtension            *self,
                                              EchoApplication          *application,
                                              GApplicationCommandLine  *command_line);
ECHO_AVAILABLE_IN_ALL
gint     echo_extension_handle_local_options (EchoExtension            *self,
                                              EchoApplication          *application,
                                              GVariantDict             *options);
ECHO_AVAILABLE_IN_ALL
gboolean echo_extension_name_lost            (EchoExtension            *self,
                                              EchoApplication          *application);
ECHO_AVAILABLE_IN_ALL
void     echo_extension_open                 (EchoExtension            *self,
                                              EchoApplication          *application,
                                              GFile                   **files,
                                              gint                      n_files,
                                              const gchar              *hint);
ECHO_AVAILABLE_IN_ALL
void     echo_extension_shutdown             (EchoExtension            *self,
                                              EchoApplication          *application);
ECHO_AVAILABLE_IN_ALL
void     echo_extension_startup              (EchoExtension            *self,
                                              EchoApplication          *application);

G_END_DECLS

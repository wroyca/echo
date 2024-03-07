/* application.h
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

#include <adwaita.h>
#include <libpeas.h>

#include <libecho/version.hxx>

G_BEGIN_DECLS

#define ECHO_TYPE_APPLICATION           (echo_application_get_type ())
#define ECHO_TYPE_APPLICATION_EXTENSION (echo_application_extension_get_type ())
#define ECHO_APPLICATION_DEFAULT        (ECHO_APPLICATION (g_application_get_default ()))
G_DECLARE_FINAL_TYPE                    (EchoApplication, echo_application, ECHO, APPLICATION, AdwApplication)
G_DECLARE_INTERFACE                     (EchoApplicationExtension, echo_application_extension, ECHO, APPLICATION_EXTENSION, GObject)

struct _EchoApplicationExtensionInterface
{
  GTypeInterface parent_interface;

  void     (*activate)             (EchoApplicationExtension  *self,
                                    EchoApplication           *application);
  gint     (*command_line)         (EchoApplicationExtension  *self,
                                    EchoApplication           *application,
                                    GApplicationCommandLine   *command_line);
  gint     (*handle_local_options) (EchoApplicationExtension  *self,
                                    EchoApplication           *application,
                                    GVariantDict              *options);
  gboolean (*name_lost)            (EchoApplicationExtension  *self,
                                    EchoApplication           *application);
  void     (*open)                 (EchoApplicationExtension  *self,
                                    EchoApplication           *application,
                                    GFile                    **files,
                                    gint                       n_files,
                                    const gchar               *hint);
  void     (*shutdown)             (EchoApplicationExtension  *self,
                                    EchoApplication           *application);
  void     (*startup)              (EchoApplicationExtension  *self,
                                    EchoApplication           *application);
};

ECHO_AVAILABLE_IN_ALL
void             echo_application_extension_activate             (EchoApplicationExtension  *self,
                                                                  EchoApplication           *application);
ECHO_AVAILABLE_IN_ALL
gint             echo_application_extension_command_line         (EchoApplicationExtension  *self,
                                                                  EchoApplication           *application,
                                                                  GApplicationCommandLine   *command_line);
ECHO_AVAILABLE_IN_ALL
gint             echo_application_extension_handle_local_options (EchoApplicationExtension  *self,
                                                                  EchoApplication           *application,
                                                                  GVariantDict              *options);
ECHO_AVAILABLE_IN_ALL
gboolean         echo_application_extension_name_lost            (EchoApplicationExtension  *self,
                                                                  EchoApplication           *application);
ECHO_AVAILABLE_IN_ALL
void             echo_application_extension_open                 (EchoApplicationExtension  *self,
                                                                  EchoApplication           *application,
                                                                  GFile                    **files,
                                                                  gint                       n_files,
                                                                  const gchar               *hint);
ECHO_AVAILABLE_IN_ALL
void             echo_application_extension_shutdown             (EchoApplicationExtension  *self,
                                                                  EchoApplication           *application);
ECHO_AVAILABLE_IN_ALL
void             echo_application_extension_startup              (EchoApplicationExtension  *self,
                                                                  EchoApplication           *application);
ECHO_AVAILABLE_IN_ALL
EchoApplication *echo_application_new                ();

G_END_DECLS


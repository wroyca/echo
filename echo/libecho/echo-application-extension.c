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

#define G_LOG_DOMAIN "ECHO-APPLICATION-EXTENSION"

#include <libecho/echo-application-extension.h>
#include <libecho/echo-application-private.h>
#include <libecho/echo-log.h>
#include <libecho/echo-global.h>

G_DEFINE_INTERFACE (EchoApplicationExtension, echo_application_extension, G_TYPE_OBJECT)

static void
echo_application_extension_real_activate (EchoApplicationExtension *self,
                                          EchoApplication          *application)
{
  ECHO_ENTRY;

  g_assert (ECHO_IS_APPLICATION_EXTENSION (self));
  g_assert (ECHO_IS_APPLICATION (application));

  ECHO_EXIT;
}


static gint
echo_application_extension_real_command_line (EchoApplicationExtension *self,
                                              EchoApplication          *application,
                                              GApplicationCommandLine  *command_line)
{
  ECHO_ENTRY;

  g_assert (ECHO_IS_APPLICATION_EXTENSION (self));
  g_assert (ECHO_IS_APPLICATION (application));
  g_assert (G_IS_APPLICATION_COMMAND_LINE (command_line));

  ECHO_RETURN (0);
}

static gint
echo_application_extension_real_handle_local_options (EchoApplicationExtension *self,
                                                      EchoApplication          *application,
                                                      GVariantDict             *options)
{
  ECHO_ENTRY;

  g_assert (ECHO_IS_APPLICATION_EXTENSION (self));
  g_assert (ECHO_IS_APPLICATION (application));
  g_assert (options != NULL);

  ECHO_RETURN (0);
}

static gboolean
echo_application_extension_real_name_lost (EchoApplicationExtension *self,
                                           EchoApplication          *application)
{
  ECHO_ENTRY;

  g_assert (ECHO_IS_APPLICATION_EXTENSION (self));
  g_assert (ECHO_IS_APPLICATION (application));

  ECHO_RETURN (FALSE);
}

static void
echo_application_extension_real_open (EchoApplicationExtension *self,
                                      EchoApplication          *application,
                                      GFile                   **files,
                                      gint                      n_files,
                                      const gchar              *hint)
{
  ECHO_ENTRY;

  g_assert (ECHO_IS_APPLICATION_EXTENSION (self));
  g_assert (ECHO_IS_APPLICATION (application));
  g_assert (files != NULL);
  g_assert (n_files > 0);
  g_assert (hint != NULL);

  ECHO_EXIT;
}

static void
echo_application_extension_real_shutdown (EchoApplicationExtension *self,
                                          EchoApplication          *application)
{
  ECHO_ENTRY;

  g_assert (ECHO_IS_APPLICATION_EXTENSION (self));
  g_assert (ECHO_IS_APPLICATION (application));

  ECHO_EXIT;
}

static void
echo_application_extension_real_startup (EchoApplicationExtension *self,
                                         EchoApplication          *application)
{
  ECHO_ENTRY;

  g_assert (ECHO_IS_APPLICATION_EXTENSION (self));
  g_assert (ECHO_IS_APPLICATION (application));

  ECHO_EXIT;
}

static void
echo_application_extension_default_init (EchoApplicationExtensionInterface *iface)
{
  iface->activate             = echo_application_extension_real_activate;
  iface->command_line         = echo_application_extension_real_command_line;
  iface->handle_local_options = echo_application_extension_real_handle_local_options;
  iface->name_lost            = echo_application_extension_real_name_lost;
  iface->open                 = echo_application_extension_real_open;
  iface->shutdown             = echo_application_extension_real_shutdown;
  iface->startup              = echo_application_extension_real_startup;
}

void
echo_application_extension_activate (EchoApplicationExtension *self,
                                     EchoApplication          *application)
{
  ECHO_ENTRY;

  g_return_if_fail (ECHO_IS_APPLICATION_EXTENSION (self));
  g_return_if_fail (ECHO_IS_APPLICATION (application));

  if (ECHO_APPLICATION_EXTENSION_GET_IFACE (self)->activate)
    ECHO_APPLICATION_EXTENSION_GET_IFACE (self)->activate (self, application);

  ECHO_EXIT;
}


gint
echo_application_extension_command_line (EchoApplicationExtension *self,
                                         EchoApplication          *application,
                                         GApplicationCommandLine  *command_line)

{
  gint ret;

  ECHO_ENTRY;

  g_return_val_if_fail (ECHO_IS_APPLICATION_EXTENSION (self), 1);
  g_return_val_if_fail (ECHO_IS_APPLICATION (application), 1);
  g_return_val_if_fail (G_IS_APPLICATION_COMMAND_LINE (command_line), 1);

  ret = 1;

  if (ECHO_APPLICATION_EXTENSION_GET_IFACE (self)->command_line)
    ret = ECHO_APPLICATION_EXTENSION_GET_IFACE (self)->command_line (self, application, command_line);

  ECHO_RETURN (ret);
}

gint
echo_application_extension_handle_local_options (EchoApplicationExtension *self,
                                                 EchoApplication          *application,
                                                 GVariantDict             *options)

{
  gint ret;

  ECHO_ENTRY;

  g_return_val_if_fail (ECHO_IS_APPLICATION_EXTENSION (self), 1);
  g_return_val_if_fail (ECHO_IS_APPLICATION (application), 1);
  g_return_val_if_fail (options != NULL, 1);

  ret = 1;

  if (ECHO_APPLICATION_EXTENSION_GET_IFACE (self)->handle_local_options)
    ret = ECHO_APPLICATION_EXTENSION_GET_IFACE (self)->handle_local_options (self, application, options);

  ECHO_RETURN (ret);
}

gboolean
echo_application_extension_name_lost (EchoApplicationExtension *self,
                                      EchoApplication          *application)
{
  gboolean ret;

  ECHO_ENTRY;

  g_return_val_if_fail (ECHO_IS_APPLICATION_EXTENSION (self), FALSE);
  g_return_val_if_fail (ECHO_IS_APPLICATION (application), FALSE);

  ret = FALSE;

  if (ECHO_APPLICATION_EXTENSION_GET_IFACE (self)->name_lost)
    ret = ECHO_APPLICATION_EXTENSION_GET_IFACE (self)->name_lost (self, application);

  ECHO_RETURN (ret);
}

void
echo_application_extension_open (EchoApplicationExtension *self,
                                 EchoApplication          *application,
                                 GFile                   **files,
                                 gint                      n_files,
                                 const gchar              *hint)
{
  ECHO_ENTRY;

  g_return_if_fail (ECHO_IS_APPLICATION_EXTENSION (self));
  g_return_if_fail (ECHO_IS_APPLICATION (application));
  g_return_if_fail (files != NULL);
  g_return_if_fail (n_files > 0);
  g_return_if_fail (hint != NULL);

  if (ECHO_APPLICATION_EXTENSION_GET_IFACE (self)->open)
    ECHO_APPLICATION_EXTENSION_GET_IFACE (self)->open (self, application, files, n_files, hint);

  ECHO_EXIT;
}

void
echo_application_extension_shutdown (EchoApplicationExtension *self,
                                     EchoApplication          *application)
{
  ECHO_ENTRY;

  g_return_if_fail (ECHO_IS_APPLICATION_EXTENSION (self));
  g_return_if_fail (ECHO_IS_APPLICATION (application));

  if (ECHO_APPLICATION_EXTENSION_GET_IFACE (self)->shutdown)
    ECHO_APPLICATION_EXTENSION_GET_IFACE (self)->shutdown (self, application);

  ECHO_EXIT;
}

void
echo_application_extension_startup (EchoApplicationExtension *self,
                                    EchoApplication          *application)
{
  ECHO_ENTRY;

  g_return_if_fail (ECHO_IS_APPLICATION_EXTENSION (self));
  g_return_if_fail (ECHO_IS_APPLICATION (application));

  if (ECHO_APPLICATION_EXTENSION_GET_IFACE (self)->startup)
    ECHO_APPLICATION_EXTENSION_GET_IFACE (self)->startup (self, application);

  ECHO_EXIT;
}

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

#define G_LOG_DOMAIN "ECHO-EXTENSION"

#include <libecho/echo-extension.h>
#include <libecho/echo-application.h>
#include <libecho/echo-log.h>
#include <libecho/echo-global.h>

#include <libpeas.h>

G_DEFINE_INTERFACE (EchoExtension, echo_extension, G_TYPE_OBJECT)

static void
echo_extension_real_activate (EchoExtension   *self,
                              EchoApplication *application)
{
  ECHO_ENTRY;

  g_assert (ECHO_IS_EXTENSION (self));
  g_assert (ECHO_IS_APPLICATION (application));

  ECHO_EXIT;
}

static gint
echo_extension_real_command_line (EchoExtension            *self,
                                  EchoApplication          *application,
                                  GApplicationCommandLine  *command_line)
{
  ECHO_ENTRY;

  g_assert (ECHO_IS_EXTENSION (self));
  g_assert (ECHO_IS_APPLICATION (application));
  g_assert (G_IS_APPLICATION_COMMAND_LINE (command_line));

  ECHO_RETURN (0);
}

static gint
echo_extension_real_handle_local_options (EchoExtension   *self,
                                          EchoApplication *application,
                                          GVariantDict    *options)
{
  ECHO_ENTRY;

  g_assert (ECHO_IS_EXTENSION (self));
  g_assert (ECHO_IS_APPLICATION (application));
  g_assert (options != NULL);

  ECHO_RETURN (0);
}

static gboolean
echo_extension_real_name_lost (EchoExtension   *self,
                               EchoApplication *application)
{
  ECHO_ENTRY;

  g_assert (ECHO_IS_EXTENSION (self));
  g_assert (ECHO_IS_APPLICATION (application));

  ECHO_RETURN (FALSE);
}

static void
echo_extension_real_open (EchoExtension    *self,
                          EchoApplication  *application,
                          GFile           **files,
                          gint              n_files,
                          const gchar      *hint)
{
  ECHO_ENTRY;

  g_assert (ECHO_IS_EXTENSION (self));
  g_assert (ECHO_IS_APPLICATION (application));
  g_assert (files != NULL);
  g_assert (n_files > 0);
  g_assert (hint != NULL);

  ECHO_EXIT;
}

static void
echo_extension_real_shutdown (EchoExtension   *self,
                              EchoApplication *application)
{
  ECHO_ENTRY;

  g_assert (ECHO_IS_EXTENSION (self));
  g_assert (ECHO_IS_APPLICATION (application));

  ECHO_EXIT;
}

static void
echo_extension_real_startup (EchoExtension   *self,
                             EchoApplication *application)
{
  ECHO_ENTRY;

  g_assert (ECHO_IS_EXTENSION (self));
  g_assert (ECHO_IS_APPLICATION (application));

  ECHO_EXIT;
}

static void
echo_extension_default_init (EchoExtensionInterface *iface)
{
  iface->activate             = echo_extension_real_activate;
  iface->command_line         = echo_extension_real_command_line;
  iface->handle_local_options = echo_extension_real_handle_local_options;
  iface->name_lost            = echo_extension_real_name_lost;
  iface->open                 = echo_extension_real_open;
  iface->shutdown             = echo_extension_real_shutdown;
  iface->startup              = echo_extension_real_startup;
}

void
echo_extension_activate (EchoExtension   *self,
                         EchoApplication *application)
{
  ECHO_ENTRY;

  g_return_if_fail (ECHO_IS_EXTENSION (self));
  g_return_if_fail (ECHO_IS_APPLICATION (application));

  if (ECHO_EXTENSION_GET_IFACE (self)->activate)
    ECHO_EXTENSION_GET_IFACE (self)->activate (self, application);

  ECHO_EXIT;
}


gint
echo_extension_command_line (EchoExtension           *self,
                             EchoApplication         *application,
                             GApplicationCommandLine *command_line)

{
  ECHO_ENTRY;

  gint ret;

  g_return_val_if_fail (ECHO_IS_EXTENSION (self), 1);
  g_return_val_if_fail (ECHO_IS_APPLICATION (application), 1);
  g_return_val_if_fail (G_IS_APPLICATION_COMMAND_LINE (command_line), 1);

  ret = 1;

  if (ECHO_EXTENSION_GET_IFACE (self)->command_line)
    ret = ECHO_EXTENSION_GET_IFACE (self)->command_line (self, application, command_line);

  ECHO_RETURN (ret);
}

gint
echo_extension_handle_local_options (EchoExtension   *self,
                                     EchoApplication *application,
                                     GVariantDict    *options)

{
  ECHO_ENTRY;

  gint ret;

  g_return_val_if_fail (ECHO_IS_EXTENSION (self), 1);
  g_return_val_if_fail (ECHO_IS_APPLICATION (application), 1);
  g_return_val_if_fail (options != NULL, 1);

  ret = 1;

  if (ECHO_EXTENSION_GET_IFACE (self)->handle_local_options)
    ret = ECHO_EXTENSION_GET_IFACE (self)->handle_local_options (self, application, options);

  ECHO_RETURN (ret);
}

gboolean
echo_extension_name_lost (EchoExtension   *self,
                          EchoApplication *application)
{
  ECHO_ENTRY;

  gboolean ret;

  g_return_val_if_fail (ECHO_IS_EXTENSION (self), FALSE);
  g_return_val_if_fail (ECHO_IS_APPLICATION (application), FALSE);

  ret = FALSE;

  if (ECHO_EXTENSION_GET_IFACE (self)->name_lost)
    ret = ECHO_EXTENSION_GET_IFACE (self)->name_lost (self, application);

  ECHO_RETURN (ret);
}

void
echo_extension_open (EchoExtension    *self,
                     EchoApplication  *application,
                     GFile           **files,
                     gint              n_files,
                     const gchar      *hint)
{
  ECHO_ENTRY;

  g_return_if_fail (ECHO_IS_EXTENSION (self));
  g_return_if_fail (ECHO_IS_APPLICATION (application));
  g_return_if_fail (files != NULL);
  g_return_if_fail (n_files > 0);
  g_return_if_fail (hint != NULL);

  if (ECHO_EXTENSION_GET_IFACE (self)->open)
    ECHO_EXTENSION_GET_IFACE (self)->open (self, application, files, n_files, hint);

  ECHO_EXIT;
}

void
echo_extension_shutdown (EchoExtension   *self,
                         EchoApplication *application)
{
  ECHO_ENTRY;

  g_return_if_fail (ECHO_IS_EXTENSION (self));
  g_return_if_fail (ECHO_IS_APPLICATION (application));

  if (ECHO_EXTENSION_GET_IFACE (self)->shutdown)
    ECHO_EXTENSION_GET_IFACE (self)->shutdown (self, application);

  ECHO_EXIT;
}

void
echo_extension_startup (EchoExtension   *self,
                        EchoApplication  *application)
{
  ECHO_ENTRY;

  g_return_if_fail (ECHO_IS_EXTENSION (self));
  g_return_if_fail (ECHO_IS_APPLICATION (application));

  if (ECHO_EXTENSION_GET_IFACE (self)->startup)
    ECHO_EXTENSION_GET_IFACE (self)->startup (self, application);

  ECHO_EXIT;
}

void
_echo_extension_init (EchoApplication *self)
{
  g_assert (ECHO_IS_MAIN_THREAD ());
  g_assert (ECHO_IS_APPLICATION (self));
  g_assert (self->extensions == NULL);

  self->extensions = peas_extension_set_new (peas_engine_get_default (),
                                             ECHO_TYPE_EXTENSION,
                                             NULL);
}

/* echo-application.c
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

#define G_LOG_DOMAIN "echo-application"

#include <libecho/echo-application.h>
#include <libecho/echo-application-private.h>
#include <libecho/echo-application-extension.h>
#include <libecho/echo-application-window-private.h>

#include <libecho/echo-private.h>
#include <libecho/echo-log.h>
#include <libecho/echo-global.h>

G_DEFINE_FINAL_TYPE (EchoApplication, echo_application, ADW_TYPE_APPLICATION)

 /**
 * echo_application_new:
 *
 * Creates a new `EchoApplication`.
 *
 * Returns: (transfer full): the newly created `EchoApplication`
 */
EchoApplication *
echo_application_new ()
{
  ECHO_ENTRY;

  g_autoptr (EchoApplication) self = NULL;

  self = g_object_new (ECHO_TYPE_APPLICATION,
                       "application-id", "app.drey.Echo",
                       "flags", G_APPLICATION_DEFAULT_FLAGS,
                       NULL);

  _echo_plugin_init (self);
  _echo_extension_init (self);

  ECHO_RETURN (g_steal_pointer (&self));
}

static void
echo_application_activate_cb (PeasExtensionSet *set,
                             PeasPluginInfo    *plugin_info,
                             GObject           *exten,
                             gpointer           user_data)
{
  g_assert (PEAS_IS_EXTENSION_SET (set));
  g_assert (plugin_info != NULL);
  g_assert (ECHO_IS_APPLICATION_EXTENSION (exten));
  g_assert (ECHO_IS_APPLICATION (user_data));

  echo_application_extension_activate (ECHO_APPLICATION_EXTENSION (exten), user_data);
}

static void
echo_application_activate (GApplication *app)
{
  ECHO_ENTRY;

  g_autoptr (EchoApplication) self = ECHO_APPLICATION (app);
  g_autoptr (EchoApplicationWindow) window = NULL;

  g_assert (ECHO_IS_MAIN_THREAD ());
  g_assert (ECHO_IS_APPLICATION (self));

  /*
   * For now, we don't have any complex initialization machinery, so we leave
   * window creating responsibilities to ECHO_APPLICATION.
   */
  window = _echo_application_get_active_window (self);
  if (window == NULL)
    window = _echo_application_window_new (self);

  if (self->extensions != NULL)
    peas_extension_set_foreach (self->extensions,
                                echo_application_activate_cb,
                                self);

  _echo_application_window_present (window);

  g_steal_pointer (&self);
  g_steal_pointer (&window);

  ECHO_EXIT;
}

static void
echo_application_class_init (EchoApplicationClass *self)
{
  ECHO_ENTRY;

  GObjectClass *obj_class = G_OBJECT_CLASS (self);
  GApplicationClass *app_class = G_APPLICATION_CLASS (self);

  app_class->activate = echo_application_activate;

  ECHO_EXIT;
}

static void
echo_application_init (EchoApplication *self)
{

  ECHO_ENTRY;
  ECHO_EXIT;
}

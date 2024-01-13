// echo-application.c
//
// Copyright 2024 William Roy
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include <libecho/echo-application-private.h>
#include <libecho/echo-application-extension.h>

G_DEFINE_FINAL_TYPE (EchoApplication, echo_application, ADW_TYPE_APPLICATION)

EchoApplication *
echo_application_new ()
{
  g_autoptr (EchoApplication) self = NULL;

  self = g_object_new (ECHO_TYPE_APPLICATION,
                       "application-id", "app.drey.Echo",
                       "flags", G_APPLICATION_DEFAULT_FLAGS,
                       NULL);

  _echo_plugin_init (self);
  _echo_extension_init (self);

  return g_steal_pointer (&self);
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
  g_autoptr (EchoApplication) self = ECHO_APPLICATION (app);
  g_autoptr (GtkWindow) window = NULL;

  g_assert (ECHO_IS_APPLICATION (self));

  if ((window = gtk_application_get_active_window (GTK_APPLICATION (self))))
    gtk_window_present (GTK_WINDOW (g_steal_pointer (&window)));

  if (self->extensions != NULL)
    peas_extension_set_foreach (self->extensions,
                                echo_application_activate_cb,
                                self);
  g_steal_pointer (&self);
}

static void
echo_application_class_init (EchoApplicationClass *klass)
{
  GObjectClass *obj_class = G_OBJECT_CLASS (klass);
  GApplicationClass *app_class = G_APPLICATION_CLASS (klass);

  app_class->activate = echo_application_activate;
}

static void
echo_application_init (EchoApplication *klass)
{

}


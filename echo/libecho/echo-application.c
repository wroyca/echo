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

#define G_LOG_DOMAIN "ECHO-APPLICATION"

#include <libecho/echo-application.h>
#include <libecho/echo-application-private.h>
#include <libecho/echo-application-extension.h>

#include <libecho/echo-log.h>
#include <libecho/echo-global.h>

typedef struct
{
  EchoApplication  *self;
  GFile           **files;
  gint              n_files;
  const gchar      *hint;
} OpenData;

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
                              PeasPluginInfo   *plugin_info,
                              GObject          *exten,
                              gpointer          user_data)
{
  ECHO_ENTRY;

  g_autoptr (EchoApplicationExtension) extension = ECHO_APPLICATION_EXTENSION (exten);

  g_assert (PEAS_IS_EXTENSION_SET (set));
  g_assert (plugin_info != NULL);
  g_assert (ECHO_IS_APPLICATION_EXTENSION (extension));
  g_assert (ECHO_IS_APPLICATION (user_data));

  echo_application_extension_activate (extension, user_data);

  g_steal_pointer (&extension);

  ECHO_EXIT;
}

static void
echo_application_activate (GApplication *app)
{
  ECHO_ENTRY;

  g_autoptr (EchoApplication) self = ECHO_APPLICATION (app);

  g_assert (ECHO_IS_MAIN_THREAD ());
  g_assert (ECHO_IS_APPLICATION (self));

  if (self->extensions != NULL)
    peas_extension_set_foreach (self->extensions,
                                echo_application_activate_cb,
                                self);

  g_steal_pointer (&self);

  ECHO_EXIT;
}

static void
echo_application_command_line_cb (PeasExtensionSet *set,
                                  PeasPluginInfo   *plugin_info,
                                  GObject          *exten,
                                  gpointer          user_data)
{
  ECHO_ENTRY;

  g_autoptr (EchoApplicationExtension) extension = ECHO_APPLICATION_EXTENSION (exten);

  g_assert (PEAS_IS_EXTENSION_SET (set));
  g_assert (plugin_info != NULL);
  g_assert (ECHO_IS_APPLICATION_EXTENSION (extension));
  g_assert (G_IS_APPLICATION_COMMAND_LINE (user_data));

  echo_application_extension_command_line (extension, ECHO_APPLICATION_DEFAULT, user_data);

  g_steal_pointer (&extension);

  ECHO_EXIT;
}

static gint
echo_application_command_line (GApplication *app,
                               GApplicationCommandLine* command_line)
{
  ECHO_ENTRY;

  g_autoptr (EchoApplication) self = ECHO_APPLICATION (app);

  g_assert (ECHO_IS_MAIN_THREAD ());
  g_assert (ECHO_IS_APPLICATION (self));

  /*
   * TODO: Chain-up plugins and handle GApplicationCommandLine.
   *
   */
  if (self->extensions != NULL)
    peas_extension_set_foreach (self->extensions,
                                echo_application_command_line_cb,
                                command_line);

  g_steal_pointer (&self);

  ECHO_RETURN (G_APPLICATION_CLASS (echo_application_parent_class)->command_line (app, command_line));
}

static void
echo_application_handle_local_options_cb (PeasExtensionSet *set,
                                          PeasPluginInfo   *plugin_info,
                                          GObject          *exten,
                                          gpointer          user_data)
{
  ECHO_ENTRY;

  g_autoptr (EchoApplicationExtension) extension = ECHO_APPLICATION_EXTENSION (exten);

  g_assert (PEAS_IS_EXTENSION_SET (set));
  g_assert (plugin_info != NULL);
  g_assert (ECHO_IS_APPLICATION_EXTENSION (extension));
  g_assert (user_data != NULL);

  echo_application_extension_handle_local_options (extension, ECHO_APPLICATION_DEFAULT, user_data);

  g_steal_pointer (&extension);

  ECHO_EXIT;
}

static gint
echo_application_handle_local_options (GApplication *app,
                                       GVariantDict* options)
{
  ECHO_ENTRY;

  g_autoptr (EchoApplication) self = ECHO_APPLICATION (app);

  g_assert (ECHO_IS_MAIN_THREAD ());
  g_assert (ECHO_IS_APPLICATION (self));

  if (self->extensions != NULL)
    peas_extension_set_foreach (self->extensions,
                                echo_application_handle_local_options_cb,
                                options);

  g_steal_pointer (&self);

  ECHO_RETURN (G_APPLICATION_CLASS (echo_application_parent_class)->handle_local_options (app, options));
}

static void
echo_application_name_lost_cb (PeasExtensionSet *set,
                               PeasPluginInfo   *plugin_info,
                               GObject          *exten,
                               gpointer          user_data)
{
  ECHO_ENTRY;

  g_autoptr (EchoApplicationExtension) extension = ECHO_APPLICATION_EXTENSION (exten);

  g_assert (PEAS_IS_EXTENSION_SET (set));
  g_assert (plugin_info != NULL);
  g_assert (ECHO_IS_APPLICATION_EXTENSION (extension));
  g_assert (ECHO_IS_APPLICATION (user_data));

  echo_application_extension_name_lost (extension, user_data);

  g_steal_pointer (&extension);

  ECHO_EXIT;
}

static gboolean
echo_application_name_lost (GApplication *app)
{
  ECHO_ENTRY;

  g_autoptr (EchoApplication) self = ECHO_APPLICATION (app);

  g_assert (ECHO_IS_MAIN_THREAD ());
  g_assert (ECHO_IS_APPLICATION (self));

  if (self->extensions != NULL)
    peas_extension_set_foreach (self->extensions,
                                echo_application_name_lost_cb,
                                self);

  g_steal_pointer (&self);

  ECHO_RETURN (G_APPLICATION_CLASS (echo_application_parent_class)->name_lost (app));
}

static void
echo_application_open_cb (PeasExtensionSet *set,
                          PeasPluginInfo   *plugin_info,
                          GObject          *exten,
                          gpointer          user_data)
{
  g_autoptr (EchoApplicationExtension) extension = ECHO_APPLICATION_EXTENSION (exten);
  OpenData *data = user_data;

  ECHO_ENTRY;

  g_assert (PEAS_IS_EXTENSION_SET (set));
  g_assert (plugin_info != NULL);
  g_assert (ECHO_IS_APPLICATION_EXTENSION (extension));
  g_assert (data != NULL);
  g_assert (ECHO_IS_APPLICATION (data->self));
  g_assert (data->files != NULL);

  echo_application_extension_open (extension, data->self, data->files, data->n_files, data->hint);

  g_steal_pointer (&extension);

  ECHO_EXIT;
}

static void
echo_application_open (GApplication  *app,
                       GFile        **files,
                       gint           n_files,
                       const gchar   *hint)
{
  g_autoptr (EchoApplication) self = ECHO_APPLICATION (app);
  OpenData data;

  ECHO_ENTRY;

  g_assert (ECHO_IS_MAIN_THREAD ());
  g_assert (ECHO_IS_APPLICATION (self));
  g_assert (files);
  g_assert (n_files > 0);
  g_assert (hint);

  data.self = self;
  data.files = files;
  data.n_files = n_files;
  data.hint = hint;

  if (self->extensions != NULL)
    peas_extension_set_foreach (self->extensions,
                                echo_application_open_cb,
                                &data);

  g_steal_pointer (&self);

  G_APPLICATION_CLASS (echo_application_parent_class)->open (app, files, n_files, hint);

  ECHO_EXIT;
}

static void
echo_application_shutdown_cb (PeasExtensionSet *set,
                              PeasPluginInfo   *plugin_info,
                              GObject          *exten,
                              gpointer          user_data)
{
  ECHO_ENTRY;

  g_autoptr (EchoApplicationExtension) extension = ECHO_APPLICATION_EXTENSION (exten);

  g_assert (PEAS_IS_EXTENSION_SET (set));
  g_assert (plugin_info != NULL);
  g_assert (ECHO_IS_APPLICATION_EXTENSION (extension));
  g_assert (ECHO_IS_APPLICATION (user_data));

  echo_application_extension_shutdown (extension, user_data);

  g_steal_pointer (&extension);

  ECHO_EXIT;
}

static void
echo_application_shutdown (GApplication *app)
{
  ECHO_ENTRY;

  g_autoptr (EchoApplication) self = ECHO_APPLICATION (app);

  g_assert (ECHO_IS_MAIN_THREAD ());
  g_assert (ECHO_IS_APPLICATION (self));

  if (self->extensions != NULL)
    peas_extension_set_foreach (self->extensions,
                                echo_application_shutdown_cb,
                                self);

  g_steal_pointer (&self);

  G_APPLICATION_CLASS (echo_application_parent_class)->shutdown (app);

  ECHO_EXIT;
}

static void
echo_application_startup_cb (PeasExtensionSet *set,
                             PeasPluginInfo   *plugin_info,
                             GObject          *exten,
                             gpointer          user_data)
{
  ECHO_ENTRY;

  g_autoptr (EchoApplicationExtension) extension = ECHO_APPLICATION_EXTENSION (exten);

  g_assert (PEAS_IS_EXTENSION_SET (set));
  g_assert (plugin_info != NULL);
  g_assert (ECHO_IS_APPLICATION_EXTENSION (extension));
  g_assert (ECHO_IS_APPLICATION (user_data));

  echo_application_extension_startup (extension, user_data);

  g_steal_pointer (&extension);

  ECHO_EXIT;
}


static void
echo_application_startup (GApplication *app)
{
  ECHO_ENTRY;

  g_autoptr (EchoApplication) self = ECHO_APPLICATION (app);

  g_assert (ECHO_IS_MAIN_THREAD ());
  g_assert (ECHO_IS_APPLICATION (self));

  if (self->extensions != NULL)
    peas_extension_set_foreach (self->extensions,
                                echo_application_startup_cb,
                                self);

  g_steal_pointer (&self);

  G_APPLICATION_CLASS (echo_application_parent_class)->startup (app);

  ECHO_EXIT;
}

static void
echo_application_class_init (EchoApplicationClass *self)
{
  ECHO_ENTRY;

  GObjectClass *obj_class = G_OBJECT_CLASS (self);
  GApplicationClass *app_class = G_APPLICATION_CLASS (self);

  app_class->activate             = echo_application_activate;
  app_class->command_line         = echo_application_command_line;
  app_class->handle_local_options = echo_application_handle_local_options;
  app_class->name_lost            = echo_application_name_lost;
  app_class->open                 = echo_application_open;
  app_class->shutdown             = echo_application_shutdown;
  app_class->startup              = echo_application_startup;

  ECHO_EXIT;
}

static void
echo_application_init (EchoApplication *self)
{

  ECHO_ENTRY;
  ECHO_EXIT;
}

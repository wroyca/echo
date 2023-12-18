/* echo-application.c
 *
 * Copyright 2023 William Roy
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

#include <echo/echo-application.h>
#include <echo/echo-window.h>

struct _EchoApplication
{
  AdwApplication parent_instance;
};

G_DEFINE_TYPE (EchoApplication, echo_application, ADW_TYPE_APPLICATION)

#define echo_application_get_active_window(x) ECHO_WINDOW (gtk_application_get_active_window (GTK_APPLICATION (x)))
#define echo_window_present(x)                             gtk_window_present (GTK_WINDOW (x))
#define echo_show_about_window(x, ...)                     adw_show_about_window (GTK_WINDOW (x), __VA_ARGS__)

EchoApplication *
echo_application_new ()
{
  EchoApplication* self;

  self = g_object_new (ECHO_TYPE_APPLICATION,
                       "application-id", "app.drey.Echo",
                       "flags", G_APPLICATION_DEFAULT_FLAGS,
                       nullptr);

  return ECHO_APPLICATION (self);
}

static void
echo_application_activate (GApplication *app)
{
  EchoApplication *self = ECHO_APPLICATION (app);
  EchoWindow *window;

  g_assert (ECHO_IS_APPLICATION (self));

  window = echo_application_get_active_window (app);

  if (window == nullptr)
    window = echo_window_new (self);

  echo_window_present (window);
}

static void
echo_application_class_init (EchoApplicationClass *klass)
{
  GApplicationClass *app_class = G_APPLICATION_CLASS (klass);

  g_assert (G_IS_APPLICATION_CLASS (app_class));

  app_class->activate = echo_application_activate;
}

static const char *developers[] = {
  "William Roy", nullptr
};

static void
echo_application_about_action (GSimpleAction *action,
                               GVariant      *parameter,
                               gpointer       user_data)
{
  EchoApplication *self = ECHO_APPLICATION (user_data);
  EchoWindow *window;

  g_assert (ECHO_IS_APPLICATION (self));

  window = echo_application_get_active_window (self);

  echo_show_about_window (window,
                         "application-name", "echo",
                         "application-icon", "app.drey.Echo",
                         "developer-name", "William Roy",
                         "version", "0.1.0",
                         "developers", developers,
                         "copyright", "© 2023 William Roy",
                         nullptr);
}

static const GActionEntry actions[] = {
  { "about", echo_application_about_action },
};

static void
echo_application_init (EchoApplication *self)
{
  GActionMap* map = G_ACTION_MAP (self);

  g_assert (G_IS_ACTION_MAP (map));

  g_action_map_add_action_entries (map, actions, G_N_ELEMENTS (actions), self);
}

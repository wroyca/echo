/* echo-application-window.c
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

#include <echo/echo-application-window.h>
#include <echo/echo-application.h>
#include <echo/echo-preferences-window.h>
#include <echo/echo-theme-selector.h>

struct _EchoApplicationWindow
{
  AdwApplicationWindow parent_instance;
  AdwHeaderBar        *header_bar;
  GtkMenuButton       *primary_menu_button;
};

G_DEFINE_FINAL_TYPE (EchoApplicationWindow, echo_application_window, ADW_TYPE_APPLICATION_WINDOW)

EchoApplicationWindow *
echo_application_window_new (EchoApplication *app)
{
  const auto self = g_object_new (ECHO_TYPE_APPLICATION_WINDOW,
                                  "application", app,
                                  nullptr);

  return ECHO_APPLICATION_WINDOW (self);
}

static void
echo_preferences_window_cb (GtkWidget  *widget,
                            const char *action,
                            GVariant   *parameter)
{
  const auto self = echo_preferences_window_new ();

  g_assert (g_strcmp0 (action, "app.preferences") == 0);
  g_assert (parameter == nullptr);

  gtk_window_set_transient_for (GTK_WINDOW (self), GTK_WINDOW (widget));
  gtk_window_present (GTK_WINDOW (self));
}

static void
echo_window_constructed (GObject *object)
{
  const auto self = ECHO_APPLICATION_WINDOW (object);

  g_assert (ECHO_IS_APPLICATION_WINDOW (self));

  G_OBJECT_CLASS (echo_application_window_parent_class)->constructed (object);

  const auto settings = echo_application_get_settings (ECHO_APPLICATION_DEFAULT);

  g_autoptr(GPropertyAction)
    style_variant = g_property_action_new ("style-variant", settings, "style-variant");
  g_action_map_add_action (G_ACTION_MAP (self), G_ACTION (style_variant));

  const auto button = gtk_menu_button_get_popover (self->primary_menu_button);
  const auto widget = g_object_new (ECHO_TYPE_THEME_SELECTOR, "action-name", "win.style-variant", nullptr);

  gtk_popover_menu_add_child (GTK_POPOVER_MENU (button), GTK_WIDGET (widget), "style-variant");
}

static void
echo_application_window_class_init (EchoApplicationWindowClass *klass)
{
  const auto object_class = G_OBJECT_CLASS (klass);
  const auto widget_class = GTK_WIDGET_CLASS (klass);
  const auto resource = "/app/drey/Echo/echo-application-window.ui";

  object_class->constructed = echo_window_constructed;

  gtk_widget_class_set_template_from_resource (widget_class, resource);
  gtk_widget_class_bind_template_child (widget_class, EchoApplicationWindow, header_bar);
  gtk_widget_class_bind_template_child (widget_class, EchoApplicationWindow, primary_menu_button);

  gtk_widget_class_install_action (widget_class, "app.preferences", nullptr, echo_preferences_window_cb);
}

static void
echo_application_window_init (EchoApplicationWindow *self)
{
  gtk_widget_init_template (GTK_WIDGET (self));
  gtk_widget_add_css_class (GTK_WIDGET (self), "devel");
}

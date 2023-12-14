// libecho/echo-application-window.cxx
//
// Copyright 2023 William Roy
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

#include <libecho/echo-application-window.hxx>
#include <libecho/echo-preferences-window.hxx>

struct _EchoApplicationWindow
{
  AdwApplicationWindow parent_instance;
  AdwHeaderBar *header_bar;
};

G_DEFINE_FINAL_TYPE (EchoApplicationWindow, echo_application_window, ADW_TYPE_APPLICATION_WINDOW)

_echo_application_window
_echo_application_window_new (_EchoApplication *app)
{
  const auto self (g_object_new (ECHO_TYPE_APPLICATION_WINDOW,
                                 "application", app,
                                 nullptr));

  return GTK_WINDOW (self);
}

static void
echo_preferences_window_cb (GtkWidget  *widget,
                            const char *action,
                            GVariant   *parameter)
{
  const auto self (_echo_preferences_window_new ());

  g_assert (g_strcmp0 (action, "app.preferences") == 0);
  g_assert (parameter == nullptr);

  gtk_window_set_transient_for (GTK_WINDOW (self), GTK_WINDOW (widget));
  gtk_window_present (GTK_WINDOW (self));
}

static void
echo_application_window_class_init (EchoApplicationWindowClass *klass)
{
  const auto widget_class (GTK_WIDGET_CLASS (klass));
  const auto resource ("/app/drey/Echo/echo-application-window.ui");

  gtk_widget_class_set_template_from_resource (widget_class, resource);
  gtk_widget_class_bind_template_child (widget_class, EchoApplicationWindow, header_bar);
  gtk_widget_class_install_action (widget_class, "app.preferences", nullptr, echo_preferences_window_cb);
}

static void
echo_application_window_init (EchoApplicationWindow *self)
{
  gtk_widget_init_template (GTK_WIDGET (self));
  gtk_widget_add_css_class (GTK_WIDGET (self), "devel");
}

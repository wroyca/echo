// libecho/echo-preferences-window.cxx
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

#include <libecho/echo-preferences-window.hxx>

struct _EchoPreferencesWindow
{
  AdwPreferencesWindow parent_instance;
};

G_DEFINE_FINAL_TYPE (EchoPreferencesWindow, echo_preferences_window, ADW_TYPE_PREFERENCES_WINDOW)

_echo_preferences_window
_echo_preferences_window_new ()
{
  const auto self (g_object_new (ECHO_TYPE_PREFERENCES_WINDOW, nullptr));

  return ECHO_PREFERENCES_WINDOW (self);
}

static void
echo_preferences_window_class_init (EchoPreferencesWindowClass *klass)
{
  const auto widget_class (GTK_WIDGET_CLASS(klass));
  const auto resource ("/app/drey/Echo/echo-preferences-window.ui");

  gtk_widget_class_set_template_from_resource(widget_class, resource);
}

static void
echo_preferences_window_init (EchoPreferencesWindow *self)
{
  gtk_widget_init_template (GTK_WIDGET (self));
}

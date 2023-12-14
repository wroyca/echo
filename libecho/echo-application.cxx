// libecho/echo-application.cxx
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

#include <libecho/echo-application.hxx>
#include <libecho/echo-application-window.hxx>

struct _EchoApplication
{
  AdwApplication parent_instance;
};

G_DEFINE_FINAL_TYPE (EchoApplication, echo_application, ADW_TYPE_APPLICATION)

_echo_application
_echo_application_new ()
{
  const auto self (g_object_new (ECHO_TYPE_APPLICATION,
                                 "application-id", "app.drey.Echo",
                                 "flags", G_APPLICATION_DEFAULT_FLAGS,
                                 nullptr));

  return _echo_application (ECHO_APPLICATION (self));
}

static void
echo_application_activate (GApplication* app)
{
  const auto self (ECHO_APPLICATION (app));

  g_assert (ECHO_IS_APPLICATION (self));

  auto window (gtk_application_get_active_window (GTK_APPLICATION (self)));

  if (window == nullptr)
    window = _echo_application_window_new (self);

  gtk_window_present (window);
}

static void
echo_application_class_init (EchoApplicationClass *klass)
{
  const auto app_class (G_APPLICATION_CLASS (klass));

  // dispatch table
  //
  app_class->activate = echo_application_activate;
}

static void
echo_application_init (EchoApplication *self)
{
}

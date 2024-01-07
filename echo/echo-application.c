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

#include <echo/echo-application.h>
#include <echo/echo-plugin.h>

struct _EchoApplication
{
  AdwApplication  parent_instance;

  GHashTable     *plugins;
};

G_DEFINE_FINAL_TYPE (EchoApplication, echo_application, ADW_TYPE_APPLICATION)

EchoApplication *
echo_application_new ()
{
  g_autoptr (EchoApplication) self = nullptr;

  self = g_object_new (ECHO_TYPE_APPLICATION,
                       "application-id", ECHO_APPLICATION_ID,
                       "flags", G_APPLICATION_DEFAULT_FLAGS,
                       nullptr);

  echo_plugin_init (self);

  return g_steal_pointer(&self);
}

static void
echo_application_activate (GApplication* application)
{

}

static void
echo_application_constructed (GObject* object)
{

}

static void
echo_application_class_init (EchoApplicationClass *klass)
{
  GApplicationClass *app_class = G_APPLICATION_CLASS (klass);
  GObjectClass *obj_class = G_OBJECT_CLASS (klass);

  app_class->activate = echo_application_activate;
  obj_class->constructed = echo_application_constructed;
}

static void
echo_application_init (EchoApplication *self)
{

}

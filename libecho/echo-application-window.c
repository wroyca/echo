// echo-application-window.c
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

#include <libecho/echo-application-window.h>

struct _EchoApplicationWindow
{
  AdwApplicationWindow parent_class;

  /* Template widgets */
  AdwHeaderBar        *header_bar;
  GtkLabel            *label;
};

G_DEFINE_FINAL_TYPE (EchoApplicationWindow,
                     echo_application_window,
                     ADW_TYPE_APPLICATION_WINDOW)

EchoApplicationWindow *
_echo_application_window_new (struct _EchoApplication* app)
{
  g_autoptr (EchoApplicationWindow) self = NULL;

  self = g_object_new (ECHO_TYPE_APPLICATION_WINDOW,
                       "application", app,
                       NULL);

  return g_steal_pointer (&self);
}

static void
echo_application_window_class_init (EchoApplicationWindowClass *klass)
{
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

  gtk_widget_class_set_template_from_resource (widget_class, "/app/drey/Echo/echo-application-window.ui");
  gtk_widget_class_bind_template_child (widget_class, EchoApplicationWindow, header_bar);
  gtk_widget_class_bind_template_child (widget_class, EchoApplicationWindow, label);
}

static void
echo_application_window_init (EchoApplicationWindow *self)
{
  gtk_widget_init_template (GTK_WIDGET (self));
}

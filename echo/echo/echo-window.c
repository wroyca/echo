/* echo-window.c
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

#include <echo/echo-window.h>

struct _EchoWindow
{
  AdwApplicationWindow  parent_instance;

  /* Template widgets */
  AdwHeaderBar         *header_bar;
  GtkLabel             *label;
};

G_DEFINE_FINAL_TYPE (EchoWindow, echo_window, ADW_TYPE_APPLICATION_WINDOW)

EchoWindow *
echo_window_new (EchoApplication *app)
{
  EchoWindow *self;

  self = g_object_new (ECHO_TYPE_WINDOW,
                       "application", app,
                       nullptr);

  return ECHO_WINDOW (self);
}

static void
echo_window_class_init (EchoWindowClass *klass)
{
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);
  const char *resource = "/app/drey/Echo/echo-window.ui";

  g_assert (GTK_IS_WIDGET_CLASS (widget_class));

  gtk_widget_class_set_template_from_resource (widget_class, resource);
  gtk_widget_class_bind_template_child (widget_class, EchoWindow, header_bar);
  gtk_widget_class_bind_template_child (widget_class, EchoWindow, label);
}

static void
echo_window_init (EchoWindow *self)
{
  gtk_widget_init_template (GTK_WIDGET (self));
}

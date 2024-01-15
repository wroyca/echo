/* echo-ui-window.c
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

#define G_LOG_DOMAIN "ECHO-UI-WINDOW"

#include <libecho/ui/echo-ui-window.h>

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
  ECHO_ENTRY;

  g_autoptr (EchoWindow) self = NULL;

  self = g_object_new (ECHO_TYPE_WINDOW,
                       "application", app,
                       NULL);

  ECHO_RETURN (g_steal_pointer (&self));
}

static void
echo_window_class_init (EchoWindowClass *klass)
{
  ECHO_ENTRY;

  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

  gtk_widget_class_set_template_from_resource (widget_class, "/app/drey/Echo/plugin/echo-ui-window.ui");
  gtk_widget_class_bind_template_child (widget_class, EchoWindow, header_bar);
  gtk_widget_class_bind_template_child (widget_class, EchoWindow, label);

  ECHO_EXIT;
}

static void
echo_window_init (EchoWindow *self)
{
  ECHO_ENTRY;

  gtk_widget_init_template (GTK_WIDGET (self));

  ECHO_EXIT;
}

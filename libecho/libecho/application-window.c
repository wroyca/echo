/* application-window.c
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

#define G_LOG_DOMAIN "ECHO-WINDOW-APPLICATION"

#include <libecho/version.h>

#include <libecho/application-window.h>
#include <libecho/trace.h>

struct _EchoApplicationWindow
{
  AdwApplicationWindow  parent_instance;

  AdwHeaderBar         *header_bar;
  PanelDock            *dock;
  PanelGrid            *grid;
};

G_DEFINE_FINAL_TYPE (EchoApplicationWindow, echo_application_window, ADW_TYPE_APPLICATION_WINDOW)

static PanelFrame *
create_frame_cb (PanelGrid             *grid,
                 EchoApplicationWindow *self)
{
  PanelFrame       *frame;
  PanelFrameHeader *header;
  AdwStatusPage    *status;
  GtkGrid          *shortcuts;
  GtkWidget        *child;

  g_assert (ECHO_IS_APPLICATION_WINDOW (self));

  frame = PANEL_FRAME (panel_frame_new ());
  status = ADW_STATUS_PAGE (adw_status_page_new ());

  adw_status_page_set_title (status, "Hello");
  adw_status_page_set_icon_name (status, "application-x-executable-symbolic");
  adw_status_page_set_description (status, "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Ut egestas.");
  panel_frame_set_placeholder (frame, GTK_WIDGET (status));

  return frame;
}

static void
echo_application_window_constructed (GObject *object)
{
  g_autoptr (EchoApplicationWindow) self = ECHO_APPLICATION_WINDOW (object);

  g_assert (ECHO_IS_APPLICATION_WINDOW (self));

  G_OBJECT_CLASS (echo_application_window_parent_class)->constructed (object);

  panel_grid_column_get_row (panel_grid_get_column (self->grid, 0), 0);

  g_steal_pointer (&self);
}

static void
echo_application_window_class_init (EchoApplicationWindowClass *klass)
{
  ECHO_ENTRY;

  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

  object_class->constructed = echo_application_window_constructed;

  gtk_widget_class_set_template_from_resource (widget_class, "/app/drey/Echo/application-window.ui");
  gtk_widget_class_bind_template_child (widget_class, EchoApplicationWindow, header_bar);
  gtk_widget_class_bind_template_child (widget_class, EchoApplicationWindow, dock);
  gtk_widget_class_bind_template_child (widget_class, EchoApplicationWindow, grid);
  gtk_widget_class_bind_template_callback (widget_class, create_frame_cb);

  ECHO_EXIT;
}

static void
echo_application_window_init (EchoApplicationWindow *self)
{
  ECHO_ENTRY;

  gtk_widget_init_template (GTK_WIDGET (self));

  ECHO_EXIT;
}

EchoApplicationWindow *
echo_application_window_new (EchoApplication *app)
{
  ECHO_ENTRY;

  g_autoptr (EchoApplicationWindow) self = NULL;

  self = g_object_new (ECHO_TYPE_APPLICATION_WINDOW,
                       "application", app,
                       NULL);

  ECHO_RETURN (g_steal_pointer (&self));
}

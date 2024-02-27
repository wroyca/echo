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

#include <glib/gi18n.h>

#include <libecho/application-window.h>
#include <libecho/trace.h>

static void
gtk_file_dialog_open_cb (GtkFileDialog         *dialog,
                         GAsyncResult          *result,
                         EchoApplicationWindow *self)
{
  g_autoptr (GFile) file = NULL;
  g_autoptr (GError) error = NULL;

  if ((file = gtk_file_dialog_open_finish (dialog, result, &error)) == nullptr)
    {
      if (!g_error_matches (error, GTK_DIALOG_ERROR, GTK_DIALOG_ERROR_CANCELLED) &&
          !g_error_matches (error, GTK_DIALOG_ERROR, GTK_DIALOG_ERROR_DISMISSED))
        g_warning ("%s(): %s", G_STRFUNC, error->message);

      return;
    }
}

void
echo_application_window_actions_open_cb (GtkWidget  *widget,
                                         const char *action_name,
                                         GVariant   *param)
{
  auto self = ECHO_APPLICATION_WINDOW (widget);
  g_autoptr (GtkFileDialog) dialog = nullptr;
  g_autoptr (GListStore) filters = nullptr;
  g_autoptr (GtkFileFilter) all_filter = nullptr;

  g_assert (ECHO_IS_APPLICATION_WINDOW (self));

  /* For the time being, permit any files and see if we should have stricter
   * filters at some point. */

  dialog = g_object_new (GTK_TYPE_FILE_DIALOG,
                         "title",        _("Select Presentation"),
                         "accept-label", _("Open"),
                         "modal",        TRUE,
                         nullptr);

  filters = g_list_store_new (GTK_TYPE_FILE_FILTER);
  all_filter = gtk_file_filter_new ();
  gtk_file_filter_set_name (all_filter, _("All Files"));
  gtk_file_filter_add_pattern (all_filter, "*");
  g_list_store_append (filters, all_filter);
  gtk_file_dialog_set_filters (dialog, G_LIST_MODEL (filters));

  /* WARN: This is asynchronous */
  gtk_file_dialog_open (dialog,
                        GTK_WINDOW (self),
                        nullptr,
                        (GAsyncReadyCallback)gtk_file_dialog_open_cb,
                        self);
}

void
_echo_application_window_class_actions_init (EchoApplicationWindowClass *klass)
{
  ECHO_ENTRY;

  auto widget_class = GTK_WIDGET_CLASS (klass);

  gtk_widget_class_install_action (widget_class,
                                   "win.open", nullptr,
                                   echo_application_window_actions_open_cb);

  ECHO_EXIT;
}

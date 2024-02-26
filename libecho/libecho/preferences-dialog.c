/* preferences-dialog.c
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

#define G_LOG_DOMAIN "ECHO-PREFERENCES-DIALOG"

#include <libecho/config.h>

#include <libecho/preferences-dialog.h>
#include <libecho/trace.h>

struct _EchoPreferencesDialog
{
  AdwPreferencesDialog parent_instance;

  AdwNavigationPage *subpage1;
  AdwNavigationPage *subpage2;
};

G_DEFINE_FINAL_TYPE (EchoPreferencesDialog, echo_preferences_dialog, ADW_TYPE_PREFERENCES_DIALOG)

EchoPreferencesDialog *
echo_preferences_dialog_new ()
{
  ECHO_ENTRY;

  auto self = g_object_new (ECHO_TYPE_PREFERENCES_DIALOG, nullptr);

  ECHO_RETURN (self);
}

static void
subpage1_activated_cb (EchoPreferencesDialog *self)
{
  ECHO_ENTRY;

  adw_preferences_dialog_push_subpage (ADW_PREFERENCES_DIALOG (self), self->subpage1);

  ECHO_EXIT;
}

static void
subpage2_activated_cb (EchoPreferencesDialog *self)
{
  ECHO_ENTRY;

  adw_preferences_dialog_push_subpage (ADW_PREFERENCES_DIALOG (self), self->subpage2);

  ECHO_EXIT;
}

static void
toast_show_cb (AdwPreferencesDialog *dialog)
{
  ECHO_ENTRY;

  adw_preferences_dialog_add_toast (dialog, adw_toast_new ("Example Toast"));

  ECHO_EXIT;
}

static void
echo_preferences_dialog_class_init (EchoPreferencesDialogClass *klass)
{
  ECHO_ENTRY;

  auto widget_class = GTK_WIDGET_CLASS (klass);
  auto resource = "/app/drey/Echo/preferences-dialog.ui";

  gtk_widget_class_set_template_from_resource (widget_class, resource);

  gtk_widget_class_bind_template_child    (widget_class, EchoPreferencesDialog, subpage1);
  gtk_widget_class_bind_template_child    (widget_class, EchoPreferencesDialog, subpage2);
  gtk_widget_class_bind_template_callback (widget_class, subpage1_activated_cb);
  gtk_widget_class_bind_template_callback (widget_class, subpage2_activated_cb);

  gtk_widget_class_install_action (widget_class, "toast.show", nullptr, (GtkWidgetActionActivateFunc) toast_show_cb);

  ECHO_EXIT;
}

static void
echo_preferences_dialog_init (EchoPreferencesDialog *self)
{
  ECHO_ENTRY;

  gtk_widget_init_template (GTK_WIDGET (self));

  ECHO_EXIT;
}

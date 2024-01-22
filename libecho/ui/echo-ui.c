/* echo-ui.c
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

#define G_LOG_DOMAIN "ECHO-UI"

#include <libecho/ui/echo-ui.h>
#include <libecho/ui/echo-ui-window.h>

struct _EchoUI
{
  GObject          parent_instance;

  EchoApplication *application;
};

extern void
echo_ui_register_types (PeasObjectModule *module)
{
  ECHO_ENTRY;

  peas_object_module_register_extension_type (module,
                                              ECHO_TYPE_EXTENSION,
                                              ECHO_TYPE_UI);

  ECHO_EXIT;
}

static void
echo_ui_activate (EchoExtension   *self,
                  EchoApplication *application)
{
  ECHO_ENTRY;

  g_autoptr (EchoWindow) window = NULL;

  g_assert (ECHO_IS_APPLICATION (application));

  window = ECHO_WINDOW (gtk_application_get_active_window (GTK_APPLICATION (application)));

  if (window == NULL)
    window = echo_window_new (application);

  gtk_window_present (GTK_WINDOW (window));

  g_steal_pointer (&window);

  ECHO_EXIT;
}

static void
echo_ui_iface_init (EchoExtensionInterface *iface)
{
  ECHO_ENTRY;

  iface->activate = echo_ui_activate;

  ECHO_EXIT;
}

G_DEFINE_FINAL_TYPE_WITH_CODE (EchoUI, echo_ui, G_TYPE_OBJECT,
                               G_IMPLEMENT_INTERFACE (ECHO_TYPE_EXTENSION, echo_ui_iface_init))

static void
echo_ui_class_init (EchoUIClass *klass)
{
  ECHO_ENTRY;

  ECHO_EXIT;
}

static void
echo_ui_init (EchoUI *self)
{
  ECHO_ENTRY;

  ECHO_EXIT;
}


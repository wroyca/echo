/* echo-plugin.c
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

#define G_LOG_DOMAIN "ECHO-PLUGIN"

#include <libecho/echo-application.h>
#include <libecho/echo-application-private.h>

#include <libecho/echo-global.h>

static gboolean
echo_plugin_can_load (PeasEngine      *engine,
                      PeasPluginInfo  *plugin_info,
                      GHashTable      *plugin_table)
{
  const char *dir;
  const char *name;
  const char *const *deps;

  g_assert (ECHO_IS_MAIN_THREAD ());
  g_assert (PEAS_IS_ENGINE (engine));
  g_assert (PEAS_IS_PLUGIN_INFO (plugin_info));

  dir = peas_plugin_info_get_module_dir (plugin_info);
  name = peas_plugin_info_get_module_name (plugin_info);

  if (g_hash_table_contains (plugin_table, name))
    {
      g_warning ("Cyclic dependency detected from %s", name);
      return FALSE;
    }

  g_hash_table_add (plugin_table, (gpointer) name);

  if ((deps = peas_plugin_info_get_dependencies (plugin_info)))
    {
      for (guint i = 0; deps[i]; i++)
        {
          g_autoptr (PeasPluginInfo) plugin_info =
            peas_engine_get_plugin_info (engine, deps[i]);

          if (!echo_plugin_can_load (engine, plugin_info, plugin_table))
          {
            g_warning ("%s doesn't meet the minimum plugin requirements", name);
            return FALSE;
          }
        }
    }

  g_hash_table_remove (plugin_table, (gpointer) name);

  return TRUE;
}

void
_echo_plugin_init (EchoApplication *self)
{
  g_autoptr (PeasEngine) engine = peas_engine_get_default ();
  guint n_items;

  g_assert (ECHO_IS_MAIN_THREAD ());
  g_assert (ECHO_IS_APPLICATION (self));

  peas_engine_add_search_path (engine,
                               "resource:///app/drey/Echo/plugin",
                               nullptr);

  n_items = g_list_model_get_n_items (G_LIST_MODEL (engine));

  for (guint i = 0; i < n_items; i++)
    {
      g_autoptr (PeasPluginInfo) plugin_info =
        g_list_model_get_item (G_LIST_MODEL (engine), i);

      if (peas_plugin_info_is_loaded (plugin_info) == 0
          && peas_plugin_info_get_external_data (plugin_info, "At-Startup"))
        {
          g_autoptr (GHashTable) plugin_table =
            g_hash_table_new (g_str_hash, g_str_equal);

          if (echo_plugin_can_load (engine, plugin_info, plugin_table))
            peas_engine_load_plugin (engine, plugin_info);
       }
    }

  g_steal_pointer (&engine);
}

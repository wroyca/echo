#include <libpeas.h>

int
main (int argc, char *argv[])
{
  const auto e (peas_engine_get_default ());
  const auto d ("/home/wroy/Projects/libecho");

  // TODO: Relocatable installation.
  //
  peas_engine_add_search_path (e, d, d);

  // Load targets through libpeas for GObject introspection.
  //
  for (guint i (0); i < g_list_model_get_n_items (G_LIST_MODEL (e)); i++)
    {
      g_autoptr (PeasPluginInfo) p
          = PEAS_PLUGIN_INFO (g_list_model_get_item (G_LIST_MODEL (e), i));

      g_message ("Loading plugin: %s",
                 peas_plugin_info_get_name (p));

      peas_engine_load_plugin (e, p);
    }
}

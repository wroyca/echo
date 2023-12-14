#include <libecho/echo.hxx>
#include <libecho/echo-application.hxx>

using namespace std;

int
main (int argc, char *argv[])
{
  const auto engine (peas_engine_get_default ());
  const auto dir ("/home/wroy/Projects/echo/libecho");

  // TODO: Relocatable installation.
  //
  peas_engine_add_search_path (engine, dir, dir);

  // Load targets through libpeas for GObject introspection.
  //
  for (guint i (0); i < g_list_model_get_n_items (G_LIST_MODEL (engine)); i++)
    {
      auto info (g_list_model_get_item (G_LIST_MODEL (engine), i));
      auto plugin (unique_ptr<PeasPluginInfo> (PEAS_PLUGIN_INFO (info)));

      g_debug ("Loading plugin: %s",
               peas_plugin_info_get_name (plugin.get ()));

      if (peas_engine_load_plugin (engine, plugin.get ()) == 0)
        return 1;
    }

  const auto app (_echo_application_new ());
  const auto ret (g_application_run (G_APPLICATION (app.get ()), argc, argv));

  return ret;
}

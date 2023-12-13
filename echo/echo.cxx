#include <libecho/echo.hxx>
#include <libecho/echo-application.hxx>

using namespace std;

int
main (int argc, char *argv[])
{
  const auto e (peas_engine_get_default ());
  const auto d ("/home/wroy/Projects/echo/libecho");

  // TODO: Relocatable installation.
  //
  peas_engine_add_search_path (e, d, d);

  // Load targets through libpeas for GObject introspection.
  //
  for (guint i (0); i < g_list_model_get_n_items (G_LIST_MODEL (e)); i++)
    {
      auto p (unique_ptr <PeasPluginInfo> (
          PEAS_PLUGIN_INFO (g_list_model_get_item (G_LIST_MODEL (e), i))));

      g_debug ("Loading plugin: %s",
               peas_plugin_info_get_name (p.get()));

      if (peas_engine_load_plugin (e, p.get()) == 0)
        return 1;
    }

  const auto a (echo_application_new ("app.drey.Echo", G_APPLICATION_DEFAULT_FLAGS));
  const auto v (g_application_run (G_APPLICATION (a.get ()), argc, argv));

  return v;
}

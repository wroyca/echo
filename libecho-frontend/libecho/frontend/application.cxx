#include <libecho/frontend/application.hxx>

#include <libecho/frontend/application-window.hxx>
#include <libecho/frontend/trace.hxx>

#include <libpeas.h>

struct _EchoApplication
{
  AdwApplication    parent_instance;

  PeasExtensionSet *extensions;
};

typedef struct
{
  EchoApplication  *self;
  GFile           **files;
  gint              n_files;
  const gchar      *hint;
} OpenData;

G_DEFINE_FINAL_TYPE (EchoApplication, echo_application, ADW_TYPE_APPLICATION)
G_DEFINE_INTERFACE  (EchoApplicationExtension, echo_application_extension, G_TYPE_OBJECT)

static void
echo_application_extension_real_activate (EchoApplicationExtension *self,
                                          EchoApplication          *application)
{
  ECHO_ENTRY;

  g_assert (ECHO_IS_APPLICATION_EXTENSION (self));
  g_assert (ECHO_IS_APPLICATION (application));

  ECHO_EXIT;
}

void
echo_application_extension_activate (EchoApplicationExtension *self,
                                     EchoApplication          *application)
{
  ECHO_ENTRY;

  g_return_if_fail (ECHO_IS_APPLICATION_EXTENSION (self));
  g_return_if_fail (ECHO_IS_APPLICATION (application));

  if (ECHO_APPLICATION_EXTENSION_GET_IFACE (self)->activate)
    ECHO_APPLICATION_EXTENSION_GET_IFACE (self)->activate (self, application);

  ECHO_EXIT;
}

static void
echo_application_activate_cb (PeasExtensionSet *set,
                              PeasPluginInfo   *plugin_info,
                              GObject          *exten,
                              gpointer          user_data)
{
  ECHO_ENTRY;

  g_autoptr (EchoApplication) self = ECHO_APPLICATION (user_data);
  g_autoptr (EchoApplicationExtension) extension = ECHO_APPLICATION_EXTENSION (exten);

  g_assert (PEAS_IS_EXTENSION_SET (set));
  g_assert (plugin_info != nullptr);
  g_assert (ECHO_IS_APPLICATION_EXTENSION (extension));
  g_assert (ECHO_IS_APPLICATION (self));

  echo_application_extension_activate (extension, self);

  g_steal_pointer (&self);
  g_steal_pointer (&extension);

  ECHO_EXIT;
}

static void
echo_application_activate (GApplication *app)
{
  ECHO_ENTRY;

  g_autoptr (EchoApplication) self = ECHO_APPLICATION (app);
  g_autoptr (EchoApplicationWindow) window = nullptr;

  g_assert (ECHO_IS_APPLICATION (self));

  if (self->extensions != nullptr)
    peas_extension_set_foreach (self->extensions,
                                echo_application_activate_cb,
                                self);

  window = ECHO_APPLICATION_WINDOW (gtk_application_get_active_window (GTK_APPLICATION (app)));

  if (window == nullptr)
    window = echo_application_window_new (self);

  gtk_window_present (GTK_WINDOW (window));

  g_steal_pointer (&self);
  g_steal_pointer (&window);

  ECHO_EXIT;
}

static gint
echo_application_extension_real_command_line (EchoApplicationExtension *self,
                                              EchoApplication          *application,
                                              GApplicationCommandLine  *command_line)
{
  ECHO_ENTRY;

  g_assert (ECHO_IS_APPLICATION_EXTENSION (self));
  g_assert (ECHO_IS_APPLICATION (application));
  g_assert (G_IS_APPLICATION_COMMAND_LINE (command_line));

  ECHO_RETURN (0);
}

gint
echo_application_extension_command_line (EchoApplicationExtension *self,
                                         EchoApplication          *application,
                                         GApplicationCommandLine  *command_line)
{
  ECHO_ENTRY;

  gint ret;

  g_return_val_if_fail (ECHO_IS_APPLICATION_EXTENSION (self), 1);
  g_return_val_if_fail (ECHO_IS_APPLICATION (application), 1);
  g_return_val_if_fail (G_IS_APPLICATION_COMMAND_LINE (command_line), 1);

  ret = 1;

  if (ECHO_APPLICATION_EXTENSION_GET_IFACE (self)->command_line)
    ret = ECHO_APPLICATION_EXTENSION_GET_IFACE (self)->command_line (self, application, command_line);

  ECHO_RETURN (ret);
}

static void
echo_application_command_line_cb (PeasExtensionSet *set,
                                  PeasPluginInfo   *plugin_info,
                                  GObject          *exten,
                                  gpointer          user_data)
{
  ECHO_ENTRY;

  g_autoptr (GApplicationCommandLine) self = G_APPLICATION_COMMAND_LINE (user_data);
  g_autoptr (EchoApplicationExtension) extension = ECHO_APPLICATION_EXTENSION (exten);

  g_assert (PEAS_IS_EXTENSION_SET (set));
  g_assert (plugin_info != nullptr);
  g_assert (ECHO_IS_APPLICATION_EXTENSION (extension));
  g_assert (G_IS_APPLICATION_COMMAND_LINE (self));

  echo_application_extension_command_line (extension, ECHO_APPLICATION_DEFAULT, self);

  g_steal_pointer (&self);
  g_steal_pointer (&extension);

  ECHO_EXIT;
}

static gint
echo_application_command_line (GApplication            *app,
                               GApplicationCommandLine *command_line)
{
  ECHO_ENTRY;

  g_autoptr (EchoApplication) self = ECHO_APPLICATION (app);

  g_assert (ECHO_IS_APPLICATION (self));

  if (self->extensions != nullptr)
    peas_extension_set_foreach (self->extensions,
                                echo_application_command_line_cb,
                                command_line);

  g_steal_pointer (&self);

  ECHO_RETURN (G_APPLICATION_CLASS (echo_application_parent_class)->command_line (app, command_line));
}

static gint
echo_application_extension_real_handle_local_options (EchoApplicationExtension *self,
                                                      EchoApplication          *application,
                                                      GVariantDict             *options)
{
  ECHO_ENTRY;

  g_assert (ECHO_IS_APPLICATION_EXTENSION (self));
  g_assert (ECHO_IS_APPLICATION (application));
  g_assert (options != nullptr);

  ECHO_RETURN (0);
}

gint
echo_application_extension_handle_local_options (EchoApplicationExtension *self,
                                                 EchoApplication          *application,
                                                 GVariantDict             *options)
{
  ECHO_ENTRY;

  gint ret;

  g_return_val_if_fail (ECHO_IS_APPLICATION_EXTENSION (self), 1);
  g_return_val_if_fail (ECHO_IS_APPLICATION (application), 1);
  g_return_val_if_fail (options != nullptr, 1);

  ret = 1;

  if (ECHO_APPLICATION_EXTENSION_GET_IFACE (self)->handle_local_options)
    ret = ECHO_APPLICATION_EXTENSION_GET_IFACE (self)->handle_local_options (self, application, options);

  ECHO_RETURN (ret);
}

static void
echo_application_handle_local_options_cb (PeasExtensionSet *set,
                                          PeasPluginInfo   *plugin_info,
                                          GObject          *exten,
                                          gpointer          user_data)
{
  ECHO_ENTRY;

  g_autoptr (EchoApplicationExtension) extension = ECHO_APPLICATION_EXTENSION (exten);

  g_assert (PEAS_IS_EXTENSION_SET (set));
  g_assert (plugin_info != nullptr);
  g_assert (ECHO_IS_APPLICATION_EXTENSION (extension));
  g_assert (user_data != nullptr);

  echo_application_extension_handle_local_options (extension, ECHO_APPLICATION_DEFAULT, std::bit_cast<GVariantDict*>(user_data));

  g_steal_pointer (&extension);

  ECHO_EXIT;
}

static gint
echo_application_handle_local_options (GApplication *app,
                                       GVariantDict *options)
{
  ECHO_ENTRY;

  g_autoptr (EchoApplication) self = ECHO_APPLICATION (app);

  g_assert (ECHO_IS_APPLICATION (self));

  if (self->extensions != nullptr)
    peas_extension_set_foreach (self->extensions,
                                echo_application_handle_local_options_cb,
                                options);

  g_steal_pointer (&self);

  ECHO_RETURN (G_APPLICATION_CLASS (echo_application_parent_class)->handle_local_options (app, options));
}

static gboolean
echo_application_extension_real_name_lost (EchoApplicationExtension *self,
                                           EchoApplication          *application)
{
  ECHO_ENTRY;

  g_assert (ECHO_IS_APPLICATION_EXTENSION (self));
  g_assert (ECHO_IS_APPLICATION (application));

  ECHO_RETURN (FALSE);
}

gboolean
echo_application_extension_name_lost (EchoApplicationExtension *self,
                                      EchoApplication          *application)
{
  ECHO_ENTRY;

  gboolean ret;

  g_return_val_if_fail (ECHO_IS_APPLICATION_EXTENSION (self), FALSE);
  g_return_val_if_fail (ECHO_IS_APPLICATION (application), FALSE);

  ret = FALSE;

  if (ECHO_APPLICATION_EXTENSION_GET_IFACE (self)->name_lost)
    ret = ECHO_APPLICATION_EXTENSION_GET_IFACE (self)->name_lost (self, application);

  ECHO_RETURN (ret);
}

static void
echo_application_name_lost_cb (PeasExtensionSet *set,
                               PeasPluginInfo   *plugin_info,
                               GObject          *exten,
                               gpointer          user_data)
{
  ECHO_ENTRY;

  g_autoptr (EchoApplication) self = ECHO_APPLICATION (user_data);
  g_autoptr (EchoApplicationExtension) extension = ECHO_APPLICATION_EXTENSION (exten);

  g_assert (PEAS_IS_EXTENSION_SET (set));
  g_assert (plugin_info != nullptr);
  g_assert (ECHO_IS_APPLICATION_EXTENSION (extension));
  g_assert (ECHO_IS_APPLICATION (self));

  echo_application_extension_name_lost (extension, self);

  g_steal_pointer (&self);
  g_steal_pointer (&extension);

  ECHO_EXIT;
}

static gboolean
echo_application_name_lost (GApplication *app)
{
  ECHO_ENTRY;

  g_autoptr (EchoApplication) self = ECHO_APPLICATION (app);

  g_assert (ECHO_IS_APPLICATION (self));

  if (self->extensions != nullptr)
    peas_extension_set_foreach (self->extensions,
                                echo_application_name_lost_cb,
                                self);

  g_steal_pointer (&self);

  ECHO_RETURN (G_APPLICATION_CLASS (echo_application_parent_class)->name_lost (app));
}

static void
echo_application_extension_real_open (EchoApplicationExtension  *self,
                                      EchoApplication           *application,
                                      GFile                    **files,
                                      gint                       n_files,
                                      const gchar               *hint)
{
  ECHO_ENTRY;

  g_assert (ECHO_IS_APPLICATION_EXTENSION (self));
  g_assert (ECHO_IS_APPLICATION (application));
  g_assert (files != nullptr);
  g_assert (n_files > 0);
  g_assert (hint != nullptr);

  ECHO_EXIT;
}

void
echo_application_extension_open (EchoApplicationExtension *self,
                                 EchoApplication          *application,
                                 GFile                   **files,
                                 gint                      n_files,
                                 const gchar              *hint)
{
  ECHO_ENTRY;

  g_return_if_fail (ECHO_IS_APPLICATION_EXTENSION (self));
  g_return_if_fail (ECHO_IS_APPLICATION (application));
  g_return_if_fail (files != nullptr);
  g_return_if_fail (n_files > 0);
  g_return_if_fail (hint != nullptr);

  if (ECHO_APPLICATION_EXTENSION_GET_IFACE (self)->open)
    ECHO_APPLICATION_EXTENSION_GET_IFACE (self)->open (self, application, files, n_files, hint);

  ECHO_EXIT;
}

static void
echo_application_open_cb (PeasExtensionSet *set,
                          PeasPluginInfo   *plugin_info,
                          GObject          *exten,
                          gpointer          user_data)
{
  ECHO_ENTRY;

  g_autoptr (EchoApplicationExtension) extension = ECHO_APPLICATION_EXTENSION (exten);
  OpenData *data = std::bit_cast<OpenData*>(user_data);

  g_assert (PEAS_IS_EXTENSION_SET (set));
  g_assert (plugin_info != nullptr);
  g_assert (ECHO_IS_APPLICATION_EXTENSION (extension));
  g_assert (data != nullptr);
  g_assert (ECHO_IS_APPLICATION (data->self));
  g_assert (data->files != nullptr);

  echo_application_extension_open (extension, data->self, data->files, data->n_files, data->hint);

  g_steal_pointer (&extension);

  ECHO_EXIT;
}

static void
echo_application_open (GApplication  *app,
                       GFile        **files,
                       gint           n_files,
                       const gchar   *hint)
{
  ECHO_ENTRY;

  g_autoptr (EchoApplication) self = ECHO_APPLICATION (app);
  OpenData data;

  g_assert (ECHO_IS_APPLICATION (self));
  g_assert (files);
  g_assert (n_files > 0);
  g_assert (hint);

  data.self = self;
  data.files = files;
  data.n_files = n_files;
  data.hint = hint;

  if (self->extensions != nullptr)
    peas_extension_set_foreach (self->extensions,
                                echo_application_open_cb,
                                &data);

  g_steal_pointer (&self);

  G_APPLICATION_CLASS (echo_application_parent_class)->open (app, files, n_files, hint);

  ECHO_EXIT;
}

static void
echo_application_extension_real_shutdown (EchoApplicationExtension *self,
                                          EchoApplication          *application)
{
  ECHO_ENTRY;

  g_assert (ECHO_IS_APPLICATION_EXTENSION (self));
  g_assert (ECHO_IS_APPLICATION (application));

  ECHO_EXIT;
}

void
echo_application_extension_shutdown (EchoApplicationExtension *self,
                                     EchoApplication          *application)
{
  ECHO_ENTRY;

  g_return_if_fail (ECHO_IS_APPLICATION_EXTENSION (self));
  g_return_if_fail (ECHO_IS_APPLICATION (application));

  if (ECHO_APPLICATION_EXTENSION_GET_IFACE (self)->shutdown)
    ECHO_APPLICATION_EXTENSION_GET_IFACE (self)->shutdown (self, application);

  ECHO_EXIT;
}

static void
echo_application_shutdown_cb (PeasExtensionSet *set,
                              PeasPluginInfo   *plugin_info,
                              GObject          *exten,
                              gpointer          user_data)
{
  ECHO_ENTRY;

  g_autoptr (EchoApplication) self = ECHO_APPLICATION (user_data);
  g_autoptr (EchoApplicationExtension) extension = ECHO_APPLICATION_EXTENSION (exten);

  g_assert (PEAS_IS_EXTENSION_SET (set));
  g_assert (plugin_info != nullptr);
  g_assert (ECHO_IS_APPLICATION_EXTENSION (extension));
  g_assert (ECHO_IS_APPLICATION (self));

  echo_application_extension_shutdown (extension, self);

  g_steal_pointer (&self);
  g_steal_pointer (&extension);

  ECHO_EXIT;
}

static void
echo_application_shutdown (GApplication *app)
{
  ECHO_ENTRY;

  g_autoptr (EchoApplication) self = ECHO_APPLICATION (app);

  g_assert (ECHO_IS_APPLICATION (self));

  if (self->extensions != nullptr)
    peas_extension_set_foreach (self->extensions,
                                echo_application_shutdown_cb,
                                self);

  g_steal_pointer (&self);

  G_APPLICATION_CLASS (echo_application_parent_class)->shutdown (app);

  ECHO_EXIT;
}

static void
echo_application_extension_real_startup (EchoApplicationExtension *self,
                                         EchoApplication          *application)
{
  ECHO_ENTRY;

  g_assert (ECHO_IS_APPLICATION_EXTENSION (self));
  g_assert (ECHO_IS_APPLICATION (application));

  ECHO_EXIT;
}

void
echo_application_extension_startup (EchoApplicationExtension *self,
                                    EchoApplication          *application)
{
  ECHO_ENTRY;

  g_return_if_fail (ECHO_IS_APPLICATION_EXTENSION (self));
  g_return_if_fail (ECHO_IS_APPLICATION (application));

  if (ECHO_APPLICATION_EXTENSION_GET_IFACE (self)->startup)
    ECHO_APPLICATION_EXTENSION_GET_IFACE (self)->startup (self, application);

  ECHO_EXIT;
}

static void
echo_application_startup_cb (PeasExtensionSet *set,
                             PeasPluginInfo   *plugin_info,
                             GObject          *exten,
                             gpointer          user_data)
{
  ECHO_ENTRY;

  g_autoptr (EchoApplication) self = ECHO_APPLICATION (user_data);
  g_autoptr (EchoApplicationExtension) extension = ECHO_APPLICATION_EXTENSION (exten);

  g_assert (PEAS_IS_EXTENSION_SET (set));
  g_assert (plugin_info != nullptr);
  g_assert (ECHO_IS_APPLICATION_EXTENSION (extension));
  g_assert (ECHO_IS_APPLICATION (self));

  echo_application_extension_startup (extension, self);

  g_steal_pointer (&self);
  g_steal_pointer (&extension);

  ECHO_EXIT;
}

static void
echo_application_startup (GApplication *app)
{
  ECHO_ENTRY;

  g_autoptr (EchoApplication) self = ECHO_APPLICATION (app);

  g_assert (ECHO_IS_APPLICATION (self));

  if (self->extensions != nullptr)
    peas_extension_set_foreach (self->extensions,
                                echo_application_startup_cb,
                                self);

  G_APPLICATION_CLASS (echo_application_parent_class)->startup (app);

  // self->settings = g_settings_new ("app.drey.Echo");

  g_steal_pointer(&self);

  ECHO_EXIT;
}

static void
echo_application_extension_default_init (EchoApplicationExtensionInterface *iface)
{
  ECHO_ENTRY;

  iface->activate             = echo_application_extension_real_activate;
  iface->command_line         = echo_application_extension_real_command_line;
  iface->handle_local_options = echo_application_extension_real_handle_local_options;
  iface->name_lost            = echo_application_extension_real_name_lost;
  iface->open                 = echo_application_extension_real_open;
  iface->shutdown             = echo_application_extension_real_shutdown;
  iface->startup              = echo_application_extension_real_startup;

  ECHO_EXIT;
}

static void
echo_application_finalize (GObject* obj)
{
  ECHO_ENTRY;

  g_autoptr (EchoApplication) self = ECHO_APPLICATION (obj);

  g_assert (ECHO_IS_APPLICATION (self));

  // g_clear_object (&self->settings);

  G_OBJECT_CLASS (echo_application_parent_class)->finalize (obj);

  g_steal_pointer (&self);

  ECHO_EXIT;
}

static void
echo_application_class_init (EchoApplicationClass *self)
{
  ECHO_ENTRY;

  GObjectClass *obj_class = G_OBJECT_CLASS (self);
  GApplicationClass *app_class = G_APPLICATION_CLASS (self);

  app_class->activate             = echo_application_activate;
  app_class->command_line         = echo_application_command_line;
  app_class->handle_local_options = echo_application_handle_local_options;
  app_class->name_lost            = echo_application_name_lost;
  app_class->open                 = echo_application_open;
  app_class->shutdown             = echo_application_shutdown;
  app_class->startup              = echo_application_startup;

  obj_class->finalize = echo_application_finalize;

  ECHO_EXIT;
}

static void
echo_application_extension_init (EchoApplication *self)
{
  ECHO_ENTRY;

  g_assert (ECHO_IS_APPLICATION (self));
  g_assert (self->extensions == nullptr);

  self->extensions = peas_extension_set_new (peas_engine_get_default (),
                                             ECHO_TYPE_APPLICATION_EXTENSION,
                                             nullptr);

  ECHO_EXIT;
}

static void
echo_application_about_action ([[maybe_unused]] GSimpleAction *action,
                               [[maybe_unused]] GVariant      *parameter,
                                                gpointer       user_data)
{
  ECHO_ENTRY;

  static const char *developers[] = {
    "William Roy", nullptr
  };

  g_autoptr (EchoApplication) self = ECHO_APPLICATION (user_data);
  g_autoptr (EchoApplicationWindow) window = nullptr;
  g_autoptr (AdwDialog) dialog = nullptr;

  g_assert (ECHO_IS_APPLICATION (self));

  window = ECHO_APPLICATION_WINDOW (gtk_application_get_active_window (GTK_APPLICATION (self)));
  dialog = ADW_DIALOG (g_object_new (ADW_TYPE_ABOUT_DIALOG,
                       "application-name", "echo",
                       "application-icon", "app.drey.Echo",
                       "developer-name", "William Roy",
                       "version", "0.1.0",
                       "developers", developers,
                       "copyright", "© 2024 William Roy",
                       nullptr));

  adw_dialog_present (dialog, GTK_WIDGET (window));

  g_steal_pointer (&self);
  g_steal_pointer (&window);
  g_steal_pointer (&dialog);
}

static void
echo_application_quit_action ([[maybe_unused]] GSimpleAction *action,
                              [[maybe_unused]] GVariant      *parameter,
                                               gpointer       user_data)
{
  ECHO_ENTRY;

  g_autoptr (EchoApplication) self = ECHO_APPLICATION (user_data);

  g_assert (ECHO_IS_APPLICATION (self));

  g_application_quit (G_APPLICATION (self));

  g_steal_pointer (&self);

  ECHO_EXIT;
}

static void
echo_application_init (EchoApplication *self)
{
  ECHO_ENTRY;

  static const GActionEntry app_actions[] = {
    { "quit",        echo_application_quit_action,        nullptr, nullptr, nullptr, {0} },
    { "about",       echo_application_about_action,       nullptr, nullptr, nullptr, {0} },
  };

  g_action_map_add_action_entries (G_ACTION_MAP (self),
                                   app_actions, G_N_ELEMENTS (app_actions),
                                   self);

  ECHO_EXIT;
}

static gboolean
echo_plugin_can_load (PeasEngine     *engine,
                      PeasPluginInfo *plugin_info,
                      GHashTable     *plugin_table)
{
  ECHO_ENTRY;

  const char *const *deps;

  g_assert (PEAS_IS_ENGINE (engine));
  g_assert (PEAS_IS_PLUGIN_INFO (plugin_info));

  const char *dir = peas_plugin_info_get_module_dir (plugin_info);
  const char *name = peas_plugin_info_get_module_name (plugin_info);

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

  ECHO_RETURN (TRUE);
}

static void
echo_plugin_init (EchoApplication *self)
{
  ECHO_ENTRY;

  g_autoptr (PeasEngine) engine = peas_engine_get_default ();

  g_assert (ECHO_IS_APPLICATION (self));

  peas_engine_add_search_path (engine,
                               "resource:///app/drey/Echo/extension",
                               nullptr);

  const auto n_items = g_list_model_get_n_items (G_LIST_MODEL (engine));

  for (guint i = 0; i < n_items; i++)
    {
      g_autoptr (PeasPluginInfo) plugin_info =
        PEAS_PLUGIN_INFO (g_list_model_get_item (G_LIST_MODEL (engine), i));

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

  ECHO_EXIT;
}

EchoApplication *
echo_application_new ()
{
  ECHO_ENTRY;

  g_autoptr (EchoApplication) self = nullptr;

  self = ECHO_APPLICATION (g_object_new (ECHO_TYPE_APPLICATION,
                                         "application-id", "app.drey.Echo",
                                         "flags", G_APPLICATION_DEFAULT_FLAGS,
                                         nullptr));

  echo_plugin_init (self);
  echo_application_extension_init (self);

  ECHO_RETURN (g_steal_pointer (&self));
}

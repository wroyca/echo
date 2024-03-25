#include <libecho/frontend/application-window.hxx>

#include <libecho/frontend/trace.hxx>

struct _EchoApplicationWindow
{
  AdwApplicationWindow  parent_instance;

  AdwHeaderBar         *header_bar;
};

G_DEFINE_FINAL_TYPE (EchoApplicationWindow, echo_application_window, ADW_TYPE_APPLICATION_WINDOW)

static void
echo_application_window_class_init (EchoApplicationWindowClass *klass)
{
  ECHO_ENTRY;

  const auto object_class (G_OBJECT_CLASS (klass));
  const auto widget_class (GTK_WIDGET_CLASS (klass));

  gtk_widget_class_set_template_from_resource (widget_class, "/app/drey/Echo/application-window.ui");
  gtk_widget_class_bind_template_child (widget_class, EchoApplicationWindow, header_bar);

  ECHO_EXIT;
}

static void
echo_application_window_init (EchoApplicationWindow *self)
{
  ECHO_ENTRY;

  gtk_widget_init_template (GTK_WIDGET (self));

#if ECHO_DEVELOP
  gtk_widget_add_css_class (GTK_WIDGET (self), "devel");
#endif

  ECHO_EXIT;
}

EchoApplicationWindow *
echo_application_window_new (EchoApplication *app)
{
  ECHO_ENTRY;

  g_autoptr (EchoApplicationWindow) self = nullptr;

  self = ECHO_APPLICATION_WINDOW (g_object_new (ECHO_TYPE_APPLICATION_WINDOW,
                                                "application", app,
                                                nullptr));

  ECHO_RETURN (g_steal_pointer (&self));
}

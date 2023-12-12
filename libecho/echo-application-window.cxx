#include <libecho/echo-application-window.hxx>

struct _EchoApplicationWindow
{
  AdwApplicationWindow parent_instance;
  AdwHeaderBar *header_bar;
};

G_DEFINE_FINAL_TYPE (EchoApplicationWindow, echo_application_window, ADW_TYPE_APPLICATION_WINDOW)

static void
echo_application_window_class_init (EchoApplicationWindowClass *klass)
{
  auto widget_class (GTK_WIDGET_CLASS (klass));
  auto resource ("/app/drey/Echo/echo-application-window.ui");

  gtk_widget_class_set_template_from_resource (widget_class, resource);
  gtk_widget_class_bind_template_child (widget_class, EchoApplicationWindow, header_bar);
}

static void
echo_application_window_init (EchoApplicationWindow *self)
{
  gtk_widget_init_template (GTK_WIDGET (self));
}

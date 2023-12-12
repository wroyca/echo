#include <libecho/echo-application-window.hxx>
#include <libecho/echo-application.hxx>

struct _EchoApplication
{
  AdwApplication parent_instance;
};

G_DEFINE_FINAL_TYPE (EchoApplication, echo_application, ADW_TYPE_APPLICATION)

std::unique_ptr <EchoApplication>
echo_application_new (const char *application_id, GApplicationFlags flags)
{
  const auto self (g_object_new (ECHO_TYPE_APPLICATION,
                                 "application-id", application_id,
                                 "flags", flags,
                                 nullptr));

  return std::unique_ptr <EchoApplication> (ECHO_APPLICATION (self));
}

static void
echo_application_activate (GApplication *app)
{
  const auto self (ECHO_APPLICATION (app));

  g_assert (ECHO_IS_APPLICATION (self));

  auto window (gtk_application_get_active_window (GTK_APPLICATION (self)));

  if (window == nullptr)
    window = GTK_WINDOW (g_object_new (ECHO_TYPE_APPLICATION_WINDOW,
                                       "application", self,
                                       nullptr));

  gtk_window_present (window);
}

static void
echo_application_class_init (EchoApplicationClass *klass)
{
  const auto app_class (G_APPLICATION_CLASS (klass));

  app_class->activate = echo_application_activate;
}

static void
echo_application_init (EchoApplication *self)
{
}

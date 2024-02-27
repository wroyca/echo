#include <adwaita.h>

#include <libecho/echo.h>

#undef NDEBUG
#include <assert.h>

static gboolean
basic_timeout_cb (gpointer data)
{
  EchoApplication* application = ECHO_APPLICATION (data);

  g_application_quit (G_APPLICATION (application));

  return G_SOURCE_REMOVE;
}

static void
test_echo_application ()
{
  g_autoptr (EchoApplication) application = NULL;
  int ret = 0;

  application = echo_application_new ();
  g_idle_add (basic_timeout_cb, application);
  ret = g_application_run (G_APPLICATION (application), 0, NULL);

  g_assert_cmpint (ret, ==, 0);
}

int
main (int   argc,
      char *argv[])
{
  gtk_test_init (&argc, &argv, NULL);

  g_test_add_func ("/libecho/application",
                   test_echo_application);

  return g_test_run();
}

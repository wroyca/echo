#include <glib/gi18n.h>

#include <libecho/echo.h>

int
main (int   argc,
      char *argv[])
{
  g_autoptr(EchoApplication) app = NULL;
  int ret;

  bindtextdomain (GETTEXT_PACKAGE, LOCALEDIR);
  bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
  textdomain (GETTEXT_PACKAGE);

  app = echo_application_new ();
  ret = g_application_run (G_APPLICATION (app), argc, argv);

  return ret;
}

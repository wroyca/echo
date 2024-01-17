#include <libecho/echo.h>

int main (int argc, char *argv[])
{
  g_autoptr (EchoApplication) app = NULL;
  int ret;

  app = _echo_application_new ();
  ret = g_application_run (G_APPLICATION (app), argc, argv);

  return ret;
}

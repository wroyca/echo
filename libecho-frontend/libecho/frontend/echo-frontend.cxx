#include <libecho/frontend/echo-frontend.hxx>
#include <libecho/frontend/application.hxx>

using namespace std;

namespace echo
{
  namespace frontend
  {
    int
    main (int argc, char *argv[])
    {
      g_autoptr (EchoApplication) app = nullptr;
      int ret;

      app = echo_application_new ();
      ret = g_application_run (G_APPLICATION (app), argc, argv);

      return ret;
    }
  }
}

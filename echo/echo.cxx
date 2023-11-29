import std;
import echo;

int
main (int argc, char *argv[])
{
  using namespace std;

  if (argc < 2)
    {
      cerr << "error: missing name" << endl;
      return 1;
    }

  echo::say_hello (argv[1]);
}

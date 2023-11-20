module;

#ifndef __cpp_lib_modules
#include <string>

#include <iostream>
#endif

module echo;

using namespace std;

namespace echo
{
  void
  say_hello (const string &n)
  {
    cout << "Hello, " << n << '!' << endl;
  }
}

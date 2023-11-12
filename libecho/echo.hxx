#pragma once

#include <iosfwd>
#include <string>

#include <libecho/export.hxx>

namespace echo
{
  // Print a greeting for the specified name into the specified
  // stream. Throw std::invalid_argument if the name is empty.
  //
  LIBECHO_SYMEXPORT void
  say_hello (std::ostream&, const std::string& name);
}

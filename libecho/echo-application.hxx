#pragma once

#include <libecho/echo.hxx>

#define ECHO_TYPE_APPLICATION (echo_application_get_type ())

G_DECLARE_FINAL_TYPE (EchoApplication, echo_application, ECHO, APPLICATION, AdwApplication)

template <>
struct std::default_delete <EchoApplication>
{
  void
  operator() (auto p) noexcept
  {
    if (p != nullptr)
      g_object_unref (p);
  }
};

std::unique_ptr <EchoApplication>
echo_application_new (const char *application_id, GApplicationFlags flags);

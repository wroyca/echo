#pragma once

#include <libecho/echo.hxx>

#define ECHO_TYPE_APPLICATION_WINDOW (echo_application_window_get_type ())

G_DECLARE_FINAL_TYPE (EchoApplicationWindow, echo_application_window, ECHO,
                      APPLICATION_WINDOW, AdwApplicationWindow)

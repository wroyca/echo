#pragma once

#include <adwaita.h>

#include <libecho/frontend/export.hxx>
#include <libecho/frontend/application.hxx>

G_BEGIN_DECLS

#define ECHO_TYPE_APPLICATION_WINDOW (echo_application_window_get_type ())
G_DECLARE_FINAL_TYPE                 (EchoApplicationWindow, echo_application_window, ECHO, APPLICATION_WINDOW, AdwApplicationWindow)

LIBECHO_FRONTEND_SYMEXPORT
EchoApplicationWindow *echo_application_window_new (EchoApplication *app);

G_END_DECLS

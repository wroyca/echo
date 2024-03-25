#pragma once

#include <adwaita.h>

#include <libecho/frontend/export.hxx>

G_BEGIN_DECLS

#define ECHO_TYPE_APPLICATION           (echo_application_get_type ())
#define ECHO_TYPE_APPLICATION_EXTENSION (echo_application_extension_get_type ())
#define ECHO_APPLICATION_DEFAULT        (ECHO_APPLICATION (g_application_get_default ()))
G_DECLARE_FINAL_TYPE                    (EchoApplication, echo_application, ECHO, APPLICATION, AdwApplication)
G_DECLARE_INTERFACE                     (EchoApplicationExtension, echo_application_extension, ECHO, APPLICATION_EXTENSION, GObject)

struct _EchoApplicationExtensionInterface
{
  GTypeInterface parent_interface;

  void     (*activate)             (EchoApplicationExtension  *self,
                                    EchoApplication           *application);
  gint     (*command_line)         (EchoApplicationExtension  *self,
                                    EchoApplication           *application,
                                    GApplicationCommandLine   *command_line);
  gint     (*handle_local_options) (EchoApplicationExtension  *self,
                                    EchoApplication           *application,
                                    GVariantDict              *options);
  gboolean (*name_lost)            (EchoApplicationExtension  *self,
                                    EchoApplication           *application);
  void     (*open)                 (EchoApplicationExtension  *self,
                                    EchoApplication           *application,
                                    GFile                    **files,
                                    gint                       n_files,
                                    const gchar               *hint);
  void     (*shutdown)             (EchoApplicationExtension  *self,
                                    EchoApplication           *application);
  void     (*startup)              (EchoApplicationExtension  *self,
                                    EchoApplication           *application);
};

LIBECHO_FRONTEND_SYMEXPORT
void             echo_application_extension_activate             (EchoApplicationExtension  *self,
                                                                  EchoApplication           *application);
LIBECHO_FRONTEND_SYMEXPORT
gint             echo_application_extension_command_line         (EchoApplicationExtension  *self,
                                                                  EchoApplication           *application,
                                                                  GApplicationCommandLine   *command_line);
LIBECHO_FRONTEND_SYMEXPORT
gint             echo_application_extension_handle_local_options (EchoApplicationExtension  *self,
                                                                  EchoApplication           *application,
                                                                  GVariantDict              *options);
LIBECHO_FRONTEND_SYMEXPORT
gboolean         echo_application_extension_name_lost            (EchoApplicationExtension  *self,
                                                                  EchoApplication           *application);
LIBECHO_FRONTEND_SYMEXPORT
void             echo_application_extension_open                 (EchoApplicationExtension  *self,
                                                                  EchoApplication           *application,
                                                                  GFile                    **files,
                                                                  gint                       n_files,
                                                                  const gchar               *hint);
LIBECHO_FRONTEND_SYMEXPORT
void             echo_application_extension_shutdown             (EchoApplicationExtension  *self,
                                                                  EchoApplication           *application);
LIBECHO_FRONTEND_SYMEXPORT
void             echo_application_extension_startup              (EchoApplicationExtension  *self,
                                                                  EchoApplication           *application);
LIBECHO_FRONTEND_SYMEXPORT
EchoApplication *echo_application_new                            ();

G_END_DECLS

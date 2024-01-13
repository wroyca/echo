// echo-application-extension.h
//
// Copyright 2024 William Roy
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <libecho/echo.h>
#include <libecho/echo-application.h>

G_BEGIN_DECLS

#define ECHO_TYPE_APPLICATION_EXTENSION (echo_application_extension_get_type())

G_DECLARE_INTERFACE (EchoApplicationExtension, echo_application_extension,
                     ECHO, APPLICATION_EXTENSION, GObject)

struct _EchoApplicationExtensionInterface
{
  GTypeInterface parent_interface;

  void (*load)     (EchoApplicationExtension  *self,
                    EchoApplication           *application);
  void (*unload)   (EchoApplicationExtension  *self,
                    EchoApplication           *application);
  void (*activate) (EchoApplicationExtension  *self,
                    EchoApplication           *application);
};

void
echo_application_extension_activate (EchoApplicationExtension *self,
                                     EchoApplication          *application);

G_END_DECLS

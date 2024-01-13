// echo-application-extension.c
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

#include <libecho/echo-application-extension.h>

G_DEFINE_INTERFACE (EchoApplicationExtension, echo_application_extension, G_TYPE_OBJECT)

void echo_application_extension_real_load   (EchoApplicationExtension *self,
                                             EchoApplication          *application) {}
void echo_application_extension_real_unload (EchoApplicationExtension *self,
                                             EchoApplication          *application) {}

static void
echo_application_extension_default_init (EchoApplicationExtensionInterface *iface)
{
  iface->load = echo_application_extension_real_load;
  iface->unload = echo_application_extension_real_unload;
}

void
echo_application_extension_activate (EchoApplicationExtension *self,
                                     EchoApplication          *application)
{
  g_return_if_fail (ECHO_IS_APPLICATION_EXTENSION (self));
  g_return_if_fail (ECHO_IS_APPLICATION (application));

  if (ECHO_APPLICATION_EXTENSION_GET_IFACE (self)->activate)
    ECHO_APPLICATION_EXTENSION_GET_IFACE (self)->activate (self, application);
}

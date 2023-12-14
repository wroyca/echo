// libecho/echo-preferences-window.hxx
//
// Copyright 2023 William Roy
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

#include <libecho/echo.hxx>

#define ECHO_TYPE_PREFERENCES_WINDOW (echo_preferences_window_get_type ())

G_DECLARE_FINAL_TYPE (EchoPreferencesWindow, echo_preferences_window, ECHO, PREFERENCES_WINDOW, AdwPreferencesWindow)

using _echo_preferences_window = EchoPreferencesWindow *;

_echo_preferences_window
_echo_preferences_window_new ();

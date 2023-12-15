/* echo-theme-selector.h
 *
 * Copyright 2023 William Roy
 * Copyright 2023 Christian Hergert
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once

#include <echo/echo.h>

G_BEGIN_DECLS

#define ECHO_TYPE_THEME_SELECTOR (echo_theme_selector_get_type ())

G_DECLARE_FINAL_TYPE (EchoThemeSelector, echo_theme_selector, ECHO, THEME_SELECTOR, GtkWidget)

EchoThemeSelector *echo_theme_selector_new ();
const char        *echo_theme_selector_get_action_name (EchoThemeSelector *self);
void               echo_theme_selector_set_action_name (EchoThemeSelector *self,
                                                        const char        *action_name);

G_END_DECLS

/* echo-version.c
 *
 * Copyright 2024 William Roy
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

#include <libecho/echo-version.h>

/**
 * echo_get_major_version:
 *
 * Get echo major version component (e.g. 1 if %ECHO_VERSION is 1.2.3)
 *
 * Returns: echo major version component.
 *
 * Since: 0.1
 */
guint
echo_get_major_version (void)
{
  return ECHO_MAJOR_VERSION;
}

/**
 * echo_get_minor_version:
 *
 * Get echo minor version component (e.g. 2 if %ECHO_VERSION is 1.2.3)
 *
 * Returns: echo minor version component.
 *
 * Since: 0.1
 */
guint
echo_get_minor_version (void)
{
  return ECHO_MINOR_VERSION;
}

/**
 * echo_get_patch_version:
 *
 * Get echo patch version component (e.g. 3 if %ECHO_VERSION is 1.2.3)
 *
 * Returns: echo minor version component.
 *
 * Since: 0.1
 */
guint
echo_get_patch_version (void)
{
  return ECHO_PATCH_VERSION;
}

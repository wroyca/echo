/* libecho/log.h
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

#pragma once

#if !defined (ECHO_INSIDE) && !defined (ECHO_COMPILATION)
#  error "Only <libecho/echo.h> can be included directly."
#endif

#include <glib.h>

G_BEGIN_DECLS

/**
 * ECHO_LOG_LEVEL_TRACE: (skip)
 *
 * The [flags@Glib.GLogLevelFlags] log level for trace messages in Echo.
 *
 * Since: 0.1
 */
#ifndef ECHO_LOG_LEVEL_TRACE
#  define ECHO_LOG_LEVEL_TRACE ((GLogLevelFlags)(1 << G_LOG_LEVEL_USER_SHIFT))
#endif

#define ECHO_ENABLE_TRACE
#ifdef ECHO_ENABLE_TRACE

/**
 * ECHO_ENTRY: (skip)
 *
 * Traces the entry into a function. Place this at the beginning of functions,
 * above pre-condition checks.
 *
 * Since: 0.1
 */

/**
 * ECHO_EXIT: (skip)
 *
 * Traces the exit from a function. Use this instead of `return` to return
 * and log the function exiting.
 *
 * Since: 0.1
 */

/**
 * ECHO_RETURN: (skip)
 * @_r: The return value
 *
 * Traces the exit from a function. Use this instead of `return` to return @_r
 * and log the function exiting.
 *
 * Since: 0.1
 */

/**
 * ECHO_GOTO: (skip)
 * @_l: The label to jump to
 *
 * Traces the jump to a label in a function. Use this instead of `goto` to jump
 * to @_l and log the label.
 *
 * Since: 0.1
 */

#define ECHO_ENTRY                                                              \
  int64_t __trace_begin_time = g_get_monotonic_time ();                         \
  g_log_structured (G_LOG_DOMAIN,                                               \
                    ECHO_LOG_LEVEL_TRACE,                                       \
                    "MESSAGE", "ENTRY: %s():%d", G_STRFUNC, __LINE__)           \

#define ECHO_EXIT                                                               \
  G_STMT_START {                                                                \
    g_log_structured (G_LOG_DOMAIN,                                             \
                      ECHO_LOG_LEVEL_TRACE,                                     \
                      "MESSAGE", "EXIT: %s():%d", G_STRFUNC, __LINE__);         \
    return;                                                                     \
  } G_STMT_END

#define ECHO_RETURN(_r)                                                         \
  G_STMT_START {                                                                \
    g_log_structured (G_LOG_DOMAIN,                                             \
                      ECHO_LOG_LEVEL_TRACE,                                     \
                      "MESSAGE", "RETURN: %s():%d ", G_STRFUNC, __LINE__);      \
    return _r;                                                                  \
  } G_STMT_END

#define ECHO_GOTO(_l)                                                           \
  G_STMT_START {                                                                \
    g_log_structured (G_LOG_DOMAIN,                                             \
                      ECHO_LOG_LEVEL_TRACE,                                     \
                      "MESSAGE", "GOTO: %s():%d ("#_l")", G_STRFUNC, __LINE__); \
    goto _l;                                                                    \
  } G_STMT_END

#else  /* ECHO_ENABLE_TRACE */

#define ECHO_ENTRY               G_STMT_START {            } G_STMT_END
#define ECHO_EXIT                G_STMT_START { return;    } G_STMT_END
#define ECHO_RETURN(_r)          G_STMT_START { return _r; } G_STMT_END
#define ECHO_GOTO(_l)            G_STMT_START { goto _l;   } G_STMT_END

#endif /* ECHO_ENABLE_TRACE */

G_END_DECLS

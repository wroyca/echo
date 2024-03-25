#pragma once

#include <glib.h>

G_BEGIN_DECLS

/**
 * ECHO_LOG_LEVEL_TRACE:
 *
 * The [flags@Glib.GLogLevelFlags] log level for trace messages in Echo.
 */
#ifndef ECHO_LOG_LEVEL_TRACE
#  define ECHO_LOG_LEVEL_TRACE ((GLogLevelFlags)(1 << G_LOG_LEVEL_USER_SHIFT))
#endif

#if ECHO_TRACE

/**
 * ECHO_ENTRY:
 *
 * Traces the entry into a function. Place this at the beginning of functions,
 * above pre-condition checks.
 */

/**
 * ECHO_EXIT:
 *
 * Traces the exit from a function. Use this instead of `return` to return
 * and log the function exiting.
 */

/**
 * ECHO_RETURN:
 * @_r: the return value
 *
 * Traces the exit from a function. Use this instead of `return` to return @_r
 * and log the function exiting.
 */

/**
 * ECHO_GOTO:
 * @_l: the label to jump to
 *
 * Traces the jump to a label in a function. Use this instead of `goto` to jump
 * to @_l and log the label.
 */

#define ECHO_ENTRY                                                              \
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

#define ECHO_ENTRY      G_STMT_START {            } G_STMT_END
#define ECHO_EXIT       G_STMT_START { return;    } G_STMT_END
#define ECHO_RETURN(_r) G_STMT_START { return _r; } G_STMT_END
#define ECHO_GOTO(_l)   G_STMT_START { goto _l;   } G_STMT_END

#endif /* ECHO_ENABLE_TRACE */

G_END_DECLS

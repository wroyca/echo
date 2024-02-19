#include <gio/gio.h>

#if defined (__ELF__) && ( __GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ >= 6))
# define SECTION __attribute__ ((section (".gresource.resource"), aligned (8)))
#else
# define SECTION
#endif

static const SECTION union { const guint8 data[2045]; const double alignment; void * const ptr;}  resource_resource_data = {
  "\107\126\141\162\151\141\156\164\000\000\000\000\000\000\000\000"
  "\030\000\000\000\254\000\000\000\000\000\000\050\005\000\000\000"
  "\000\000\000\000\002\000\000\000\003\000\000\000\004\000\000\000"
  "\005\000\000\000\324\265\002\000\377\377\377\377\254\000\000\000"
  "\001\000\114\000\260\000\000\000\264\000\000\000\047\125\001\226"
  "\002\000\000\000\264\000\000\000\005\000\114\000\274\000\000\000"
  "\300\000\000\000\244\233\210\013\000\000\000\000\300\000\000\000"
  "\004\000\114\000\304\000\000\000\310\000\000\000\172\006\340\346"
  "\004\000\000\000\310\000\000\000\025\000\166\000\340\000\000\000"
  "\361\007\000\000\265\122\060\045\001\000\000\000\361\007\000\000"
  "\005\000\114\000\370\007\000\000\374\007\000\000\057\000\000\000"
  "\002\000\000\000\144\162\145\171\057\000\000\000\004\000\000\000"
  "\141\160\160\057\001\000\000\000\141\160\160\154\151\143\141\164"
  "\151\157\156\055\167\151\156\144\157\167\056\165\151\000\000\000"
  "\001\007\000\000\000\000\000\000\074\077\170\155\154\040\166\145"
  "\162\163\151\157\156\075\042\061\056\060\042\040\145\156\143\157"
  "\144\151\156\147\075\042\125\124\106\055\070\042\077\076\012\074"
  "\151\156\164\145\162\146\141\143\145\076\074\162\145\161\165\151"
  "\162\145\163\040\154\151\142\075\042\147\164\153\042\040\166\145"
  "\162\163\151\157\156\075\042\064\056\060\042\057\076\074\162\145"
  "\161\165\151\162\145\163\040\154\151\142\075\042\101\144\167\042"
  "\040\166\145\162\163\151\157\156\075\042\061\056\060\042\057\076"
  "\074\162\145\161\165\151\162\145\163\040\154\151\142\075\042\120"
  "\141\156\145\154\042\040\166\145\162\163\151\157\156\075\042\061"
  "\056\060\042\057\076\074\164\145\155\160\154\141\164\145\040\143"
  "\154\141\163\163\075\042\105\143\150\157\101\160\160\154\151\143"
  "\141\164\151\157\156\127\151\156\144\157\167\042\040\160\141\162"
  "\145\156\164\075\042\101\144\167\101\160\160\154\151\143\141\164"
  "\151\157\156\127\151\156\144\157\167\042\076\074\160\162\157\160"
  "\145\162\164\171\040\156\141\155\145\075\042\144\145\146\141\165"
  "\154\164\055\167\151\144\164\150\042\076\066\060\060\074\057\160"
  "\162\157\160\145\162\164\171\076\074\160\162\157\160\145\162\164"
  "\171\040\156\141\155\145\075\042\144\145\146\141\165\154\164\055"
  "\150\145\151\147\150\164\042\076\063\060\060\074\057\160\162\157"
  "\160\145\162\164\171\076\074\160\162\157\160\145\162\164\171\040"
  "\156\141\155\145\075\042\143\157\156\164\145\156\164\042\076\074"
  "\157\142\152\145\143\164\040\143\154\141\163\163\075\042\101\144"
  "\167\124\157\157\154\142\141\162\126\151\145\167\042\076\074\143"
  "\150\151\154\144\076\074\157\142\152\145\143\164\040\143\154\141"
  "\163\163\075\042\120\141\156\145\154\104\157\143\153\042\040\151"
  "\144\075\042\144\157\143\153\042\076\074\160\162\157\160\145\162"
  "\164\171\040\156\141\155\145\075\042\162\145\166\145\141\154\055"
  "\142\157\164\164\157\155\042\076\146\141\154\163\145\074\057\160"
  "\162\157\160\145\162\164\171\076\074\160\162\157\160\145\162\164"
  "\171\040\156\141\155\145\075\042\162\145\166\145\141\154\055\145"
  "\156\144\042\076\146\141\154\163\145\074\057\160\162\157\160\145"
  "\162\164\171\076\074\160\162\157\160\145\162\164\171\040\156\141"
  "\155\145\075\042\162\145\166\145\141\154\055\163\164\141\162\164"
  "\042\076\146\141\154\163\145\074\057\160\162\157\160\145\162\164"
  "\171\076\074\143\150\151\154\144\040\151\156\164\145\162\156\141"
  "\154\055\143\150\151\154\144\075\042\143\145\156\164\145\162\042"
  "\076\074\157\142\152\145\143\164\040\143\154\141\163\163\075\042"
  "\120\141\156\145\154\104\157\143\153\103\150\151\154\144\042\076"
  "\074\160\162\157\160\145\162\164\171\040\156\141\155\145\075\042"
  "\143\150\151\154\144\042\076\074\157\142\152\145\143\164\040\143"
  "\154\141\163\163\075\042\120\141\156\145\154\107\162\151\144\042"
  "\040\151\144\075\042\147\162\151\144\042\076\074\163\151\147\156"
  "\141\154\040\156\141\155\145\075\042\143\162\145\141\164\145\055"
  "\146\162\141\155\145\042\040\150\141\156\144\154\145\162\075\042"
  "\143\162\145\141\164\145\137\146\162\141\155\145\137\143\142\042"
  "\057\076\074\057\157\142\152\145\143\164\076\074\057\160\162\157"
  "\160\145\162\164\171\076\074\160\162\157\160\145\162\164\171\040"
  "\156\141\155\145\075\042\164\157\160\055\145\144\147\145\042\076"
  "\074\157\142\152\145\143\164\040\143\154\141\163\163\075\042\101"
  "\144\167\110\145\141\144\145\162\102\141\162\042\040\151\144\075"
  "\042\150\145\141\144\145\162\137\142\141\162\042\076\074\143\150"
  "\151\154\144\040\164\171\160\145\075\042\163\164\141\162\164\042"
  "\076\074\157\142\152\145\143\164\040\143\154\141\163\163\075\042"
  "\120\141\156\145\154\124\157\147\147\154\145\102\165\164\164\157"
  "\156\042\076\074\160\162\157\160\145\162\164\171\040\156\141\155"
  "\145\075\042\144\157\143\153\042\076\144\157\143\153\074\057\160"
  "\162\157\160\145\162\164\171\076\074\160\162\157\160\145\162\164"
  "\171\040\156\141\155\145\075\042\141\162\145\141\042\076\163\164"
  "\141\162\164\074\057\160\162\157\160\145\162\164\171\076\074\057"
  "\157\142\152\145\143\164\076\074\057\143\150\151\154\144\076\074"
  "\143\150\151\154\144\040\164\171\160\145\075\042\145\156\144\042"
  "\076\074\157\142\152\145\143\164\040\143\154\141\163\163\075\042"
  "\107\164\153\115\145\156\165\102\165\164\164\157\156\042\076\074"
  "\160\162\157\160\145\162\164\171\040\156\141\155\145\075\042\160"
  "\162\151\155\141\162\171\042\076\124\162\165\145\074\057\160\162"
  "\157\160\145\162\164\171\076\074\160\162\157\160\145\162\164\171"
  "\040\156\141\155\145\075\042\151\143\157\156\055\156\141\155\145"
  "\042\076\157\160\145\156\055\155\145\156\165\055\163\171\155\142"
  "\157\154\151\143\074\057\160\162\157\160\145\162\164\171\076\074"
  "\160\162\157\160\145\162\164\171\040\156\141\155\145\075\042\164"
  "\157\157\154\164\151\160\055\164\145\170\164\042\040\164\162\141"
  "\156\163\154\141\164\141\142\154\145\075\042\171\145\163\042\076"
  "\115\145\156\165\074\057\160\162\157\160\145\162\164\171\076\074"
  "\160\162\157\160\145\162\164\171\040\156\141\155\145\075\042\155"
  "\145\156\165\055\155\157\144\145\154\042\076\160\162\151\155\141"
  "\162\171\137\155\145\156\165\074\057\160\162\157\160\145\162\164"
  "\171\076\074\057\157\142\152\145\143\164\076\074\057\143\150\151"
  "\154\144\076\074\057\157\142\152\145\143\164\076\074\057\160\162"
  "\157\160\145\162\164\171\076\074\057\157\142\152\145\143\164\076"
  "\074\057\143\150\151\154\144\076\074\057\157\142\152\145\143\164"
  "\076\074\057\143\150\151\154\144\076\074\057\157\142\152\145\143"
  "\164\076\074\057\160\162\157\160\145\162\164\171\076\074\057\164"
  "\145\155\160\154\141\164\145\076\074\155\145\156\165\040\151\144"
  "\075\042\160\162\151\155\141\162\171\137\155\145\156\165\042\076"
  "\074\163\145\143\164\151\157\156\076\074\151\164\145\155\076\074"
  "\141\164\164\162\151\142\165\164\145\040\156\141\155\145\075\042"
  "\154\141\142\145\154\042\040\164\162\141\156\163\154\141\164\141"
  "\142\154\145\075\042\171\145\163\042\076\137\120\162\145\146\145"
  "\162\145\156\143\145\163\074\057\141\164\164\162\151\142\165\164"
  "\145\076\074\141\164\164\162\151\142\165\164\145\040\156\141\155"
  "\145\075\042\141\143\164\151\157\156\042\076\141\160\160\056\160"
  "\162\145\146\145\162\145\156\143\145\163\074\057\141\164\164\162"
  "\151\142\165\164\145\076\074\057\151\164\145\155\076\074\151\164"
  "\145\155\076\074\141\164\164\162\151\142\165\164\145\040\156\141"
  "\155\145\075\042\154\141\142\145\154\042\040\164\162\141\156\163"
  "\154\141\164\141\142\154\145\075\042\171\145\163\042\076\137\113"
  "\145\171\142\157\141\162\144\040\123\150\157\162\164\143\165\164"
  "\163\074\057\141\164\164\162\151\142\165\164\145\076\074\141\164"
  "\164\162\151\142\165\164\145\040\156\141\155\145\075\042\141\143"
  "\164\151\157\156\042\076\167\151\156\056\163\150\157\167\055\150"
  "\145\154\160\055\157\166\145\162\154\141\171\074\057\141\164\164"
  "\162\151\142\165\164\145\076\074\057\151\164\145\155\076\074\151"
  "\164\145\155\076\074\141\164\164\162\151\142\165\164\145\040\156"
  "\141\155\145\075\042\154\141\142\145\154\042\040\164\162\141\156"
  "\163\154\141\164\141\142\154\145\075\042\171\145\163\042\076\137"
  "\101\142\157\165\164\040\105\143\150\157\074\057\141\164\164\162"
  "\151\142\165\164\145\076\074\141\164\164\162\151\142\165\164\145"
  "\040\156\141\155\145\075\042\141\143\164\151\157\156\042\076\141"
  "\160\160\056\141\142\157\165\164\074\057\141\164\164\162\151\142"
  "\165\164\145\076\074\057\151\164\145\155\076\074\057\163\145\143"
  "\164\151\157\156\076\074\057\155\145\156\165\076\074\057\151\156"
  "\164\145\162\146\141\143\145\076\012\000\000\050\165\165\141\171"
  "\051\105\143\150\157\057\000\000\003\000\000\000" };

static GStaticResource static_resource = { resource_resource_data.data, sizeof (resource_resource_data.data) - 1 /* nul terminator */, NULL, NULL, NULL };

G_MODULE_EXPORT
GResource *resource_get_resource (void);
GResource *resource_get_resource (void)
{
  return g_static_resource_get_resource (&static_resource);
}
/* GLIB - Library of useful routines for C programming
 * Copyright (C) 1995-1997  Peter Mattis, Spencer Kimball and Josh MacDonald
 *
 * SPDX-License-Identifier: LGPL-2.1-or-later
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, see <http://www.gnu.org/licenses/>.
 */

/*
 * Modified by the GLib Team and others 1997-2000.  See the AUTHORS
 * file for a list of people on the GLib Team.  See the ChangeLog
 * files for a list of changes.  These files are distributed with
 * GLib at ftp://ftp.gtk.org/pub/gtk/.
 */

#ifndef __G_CONSTRUCTOR_H__
#define __G_CONSTRUCTOR_H__

/*
  If G_HAS_CONSTRUCTORS is true then the compiler support *both* constructors and
  destructors, in a usable way, including e.g. on library unload. If not you're on
  your own.

  Some compilers need #pragma to handle this, which does not work with macros,
  so the way you need to use this is (for constructors):

  #ifdef G_DEFINE_CONSTRUCTOR_NEEDS_PRAGMA
  #pragma G_DEFINE_CONSTRUCTOR_PRAGMA_ARGS(my_constructor)
  #endif
  G_DEFINE_CONSTRUCTOR(my_constructor)
  static void my_constructor(void) {
   ...
  }

*/

#ifndef __GTK_DOC_IGNORE__

#if  __GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ >= 7)

#define G_HAS_CONSTRUCTORS 1

#define G_DEFINE_CONSTRUCTOR(_func) static void __attribute__((constructor)) _func (void);
#define G_DEFINE_DESTRUCTOR(_func) static void __attribute__((destructor)) _func (void);

#elif defined (_MSC_VER) && (_MSC_VER >= 1500)
/* Visual studio 2008 and later has _Pragma */

/*
 * Only try to include gslist.h if not already included via glib.h,
 * so that items using gconstructor.h outside of GLib (such as
 * GResources) continue to build properly.
 */
#ifndef __G_LIB_H__
#include "gslist.h"
#endif

#include <stdlib.h>

#define G_HAS_CONSTRUCTORS 1

/* We do some weird things to avoid the constructors being optimized
 * away on VS2015 if WholeProgramOptimization is enabled. First we
 * make a reference to the array from the wrapper to make sure its
 * references. Then we use a pragma to make sure the wrapper function
 * symbol is always included at the link stage. Also, the symbols
 * need to be extern (but not dllexport), even though they are not
 * really used from another object file.
 */

/* We need to account for differences between the mangling of symbols
 * for x86 and x64/ARM/ARM64 programs, as symbols on x86 are prefixed
 * with an underscore but symbols on x64/ARM/ARM64 are not.
 */
#ifdef _M_IX86
#define G_MSVC_SYMBOL_PREFIX "_"
#else
#define G_MSVC_SYMBOL_PREFIX ""
#endif

#define G_DEFINE_CONSTRUCTOR(_func) G_MSVC_CTOR (_func, G_MSVC_SYMBOL_PREFIX)
#define G_DEFINE_DESTRUCTOR(_func) G_MSVC_DTOR (_func, G_MSVC_SYMBOL_PREFIX)

#define G_MSVC_CTOR(_func,_sym_prefix) \
  static void _func(void); \
  extern int (* _array ## _func)(void);              \
  int _func ## _wrapper(void);              \
  int _func ## _wrapper(void) { _func(); g_slist_find (NULL,  _array ## _func); return 0; } \
  __pragma(comment(linker,"/include:" _sym_prefix # _func "_wrapper")) \
  __pragma(section(".CRT$XCU",read)) \
  __declspec(allocate(".CRT$XCU")) int (* _array ## _func)(void) = _func ## _wrapper;

#define G_MSVC_DTOR(_func,_sym_prefix) \
  static void _func(void); \
  extern int (* _array ## _func)(void);              \
  int _func ## _constructor(void);              \
  int _func ## _constructor(void) { atexit (_func); g_slist_find (NULL,  _array ## _func); return 0; } \
   __pragma(comment(linker,"/include:" _sym_prefix # _func "_constructor")) \
  __pragma(section(".CRT$XCU",read)) \
  __declspec(allocate(".CRT$XCU")) int (* _array ## _func)(void) = _func ## _constructor;

#elif defined (_MSC_VER)

#define G_HAS_CONSTRUCTORS 1

/* Pre Visual studio 2008 must use #pragma section */
#define G_DEFINE_CONSTRUCTOR_NEEDS_PRAGMA 1
#define G_DEFINE_DESTRUCTOR_NEEDS_PRAGMA 1

#define G_DEFINE_CONSTRUCTOR_PRAGMA_ARGS(_func) \
  section(".CRT$XCU",read)
#define G_DEFINE_CONSTRUCTOR(_func) \
  static void _func(void); \
  static int _func ## _wrapper(void) { _func(); return 0; } \
  __declspec(allocate(".CRT$XCU")) static int (*p)(void) = _func ## _wrapper;

#define G_DEFINE_DESTRUCTOR_PRAGMA_ARGS(_func) \
  section(".CRT$XCU",read)
#define G_DEFINE_DESTRUCTOR(_func) \
  static void _func(void); \
  static int _func ## _constructor(void) { atexit (_func); return 0; } \
  __declspec(allocate(".CRT$XCU")) static int (* _array ## _func)(void) = _func ## _constructor;

#elif defined(__SUNPRO_C)

/* This is not tested, but i believe it should work, based on:
 * http://opensource.apple.com/source/OpenSSL098/OpenSSL098-35/src/fips/fips_premain.c
 */

#define G_HAS_CONSTRUCTORS 1

#define G_DEFINE_CONSTRUCTOR_NEEDS_PRAGMA 1
#define G_DEFINE_DESTRUCTOR_NEEDS_PRAGMA 1

#define G_DEFINE_CONSTRUCTOR_PRAGMA_ARGS(_func) \
  init(_func)
#define G_DEFINE_CONSTRUCTOR(_func) \
  static void _func(void);

#define G_DEFINE_DESTRUCTOR_PRAGMA_ARGS(_func) \
  fini(_func)
#define G_DEFINE_DESTRUCTOR(_func) \
  static void _func(void);

#else

/* constructors not supported for this compiler */

#endif

#endif /* __GTK_DOC_IGNORE__ */
#endif /* __G_CONSTRUCTOR_H__ */

#ifdef G_HAS_CONSTRUCTORS

#ifdef G_DEFINE_CONSTRUCTOR_NEEDS_PRAGMA
#pragma G_DEFINE_CONSTRUCTOR_PRAGMA_ARGS(resourceresource_constructor)
#endif
G_DEFINE_CONSTRUCTOR(resourceresource_constructor)
#ifdef G_DEFINE_DESTRUCTOR_NEEDS_PRAGMA
#pragma G_DEFINE_DESTRUCTOR_PRAGMA_ARGS(resourceresource_destructor)
#endif
G_DEFINE_DESTRUCTOR(resourceresource_destructor)

#else
#warning "Constructor not supported on this compiler, linking in resources will not work"
#endif

static void resourceresource_constructor (void)
{
  g_static_resource_init (&static_resource);
}

static void resourceresource_destructor (void)
{
  g_static_resource_fini (&static_resource);
}

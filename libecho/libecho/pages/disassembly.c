/* disassembly.c
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

#include <libecho/pages/disassembly.h>
#include <libecho/trace.h>

struct _EchoDisassembly
{
  PanelWidget   parent_instance;

  GtkTextView  *text_view;
};

G_DEFINE_TYPE (EchoDisassembly, echo_disassembly, PANEL_TYPE_WIDGET)

static GtkWidget *
echo_disassembly_get_default_focus (PanelWidget *widget)
{
  ECHO_ENTRY;

  ECHO_RETURN (GTK_WIDGET (ECHO_DISASSEMBLY (widget)->text_view));
}

static void
echo_disassembly_class_init (EchoDisassemblyClass *klass)
{
  ECHO_ENTRY;

  auto panel_widget_class = PANEL_WIDGET_CLASS (klass);

  panel_widget_class->get_default_focus = echo_disassembly_get_default_focus;

  ECHO_EXIT;
}

static void
echo_disassembly_init (EchoDisassembly *self)
{
  ECHO_ENTRY;

  auto scroller = gtk_scrolled_window_new ();

  panel_widget_set_child (PANEL_WIDGET (self), scroller);

  self->text_view = GTK_TEXT_VIEW (gtk_text_view_new ());
  g_object_set (self->text_view, "monospace", TRUE, "left-margin", 6, "top-margin", 6, NULL);
  gtk_scrolled_window_set_child (GTK_SCROLLED_WINDOW (scroller), GTK_WIDGET (self->text_view));

  ECHO_EXIT;
}

EchoDisassembly *
echo_disassembly_new ()
{
  ECHO_ENTRY;

  auto self = g_object_new (ECHO_TYPE_DISASSEMBLY, NULL);

  ECHO_RETURN (self);
}

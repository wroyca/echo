/* application-window.cxx
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

#define G_LOG_DOMAIN "ECHO-APPLICATION-WINDOW"

#include <libecho/config.hxx>

#include <libecho/application-window.hxx>
#include <libecho/trace.hxx>
#include <libecho/version.hxx>

struct _EchoApplicationWindow
{
  AdwApplicationWindow  parent_instance;

  AdwHeaderBar         *header_bar;
  GtkTextView          *text_view;
  GtkTextBuffer        *text_buffer;
};

G_DEFINE_FINAL_TYPE (EchoApplicationWindow, echo_application_window, ADW_TYPE_APPLICATION_WINDOW)

static void
echo_application_window_class_init (EchoApplicationWindowClass *klass)
{
  ECHO_ENTRY;

  const auto object_class = G_OBJECT_CLASS (klass);
  const auto widget_class = GTK_WIDGET_CLASS (klass);

  gtk_widget_class_set_template_from_resource (widget_class, "/app/drey/Echo/application-window.ui");
  gtk_widget_class_bind_template_child (widget_class, EchoApplicationWindow, header_bar);
  gtk_widget_class_bind_template_child (widget_class, EchoApplicationWindow, text_view);
  gtk_widget_class_bind_template_child (widget_class, EchoApplicationWindow, text_buffer);

  ECHO_EXIT;
}

static void
echo_application_window_init (EchoApplicationWindow *self)
{
  ECHO_ENTRY;

  gtk_widget_init_template (GTK_WIDGET (self));

#if ECHO_DEVELOP
  gtk_widget_add_css_class (GTK_WIDGET (self), "devel");
#endif

  // XXX: This is a sample for visual feedback, it will be removed.
  //
  void
  sample (EchoApplicationWindow *self);
  sample (self);

  ECHO_EXIT;
}

EchoApplicationWindow *
echo_application_window_new (EchoApplication *app)
{
  ECHO_ENTRY;

  g_autoptr (EchoApplicationWindow) self = nullptr;

  self = ECHO_APPLICATION_WINDOW (g_object_new (ECHO_TYPE_APPLICATION_WINDOW,
                                  "application", app,
                                  nullptr));

  ECHO_RETURN (g_steal_pointer (&self));
}

#include <LIEF/LIEF.hpp>
#include <Zydis/Zydis.h>
#include <Zycore/Format.h>

void
sample (EchoApplicationWindow *self)
{
  using namespace std;
  using namespace LIEF::ELF;

  ZydisDecoder decoder;
  ZydisDecoderInit(&decoder, ZYDIS_MACHINE_MODE_LONG_64, ZYDIS_STACK_WIDTH_64);
  ZydisFormatter fmt;
  ZydisFormatterInit(&fmt, ZYDIS_FORMATTER_STYLE_INTEL);
  ZydisDecodedInstruction instr;
  ZydisDecodedOperand operands[ZYDIS_MAX_OPERAND_COUNT];

  auto elf = Parser::parse ("/home/wroy/Projects/echo/etc/sample");
  auto elf_text_section (elf->get_section (".text"));
  auto elf_text_section_content (elf_text_section->content());
  auto elf_text_section_content_data (elf_text_section_content.data());
  auto elf_text_section_content_size (elf_text_section_content.size());
  auto elf_text_section_content_instruction (vector <string>{});

  ZyanU64 addr (0x007FFFFFFF400000);
  ZyanUSize offset (elf_text_section->virtual_address());

  while (ZYAN_SUCCESS(ZydisDecoderDecodeFull(&decoder,
                                             elf_text_section_content_data,
                                             elf_text_section_content_size,
                                             &instr,
                                             operands)))
  {
    char buffer[256];
    ZydisFormatterFormatInstruction (&fmt,
                                     &instr,
                                     operands,
                                     instr.operand_count_visible,
                                     buffer,
                                     sizeof (buffer),
                                     addr,
                                     nullptr);

    elf_text_section_content_instruction.push_back(buffer);
    elf_text_section_content_data += instr.length;
    elf_text_section_content_size -= instr.length;
  }

  GtkTextIter iter;
  for (auto &instruction : elf_text_section_content_instruction)
  {
    gtk_text_buffer_get_end_iter(self->text_buffer, &iter);
    gtk_text_buffer_insert(self->text_buffer, &iter, instruction.c_str(), -1);
    gtk_text_buffer_insert(self->text_buffer, &iter, "\n", -1);
  }
}

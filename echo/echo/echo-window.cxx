/* echo-window.c
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

#include <echo/config.hxx>

#include <echo/echo-window.hxx>

struct _EchoWindow
{
	AdwApplicationWindow  parent_instance;

	/* Template widgets */
	AdwHeaderBar         *header_bar;
	GtkTextView          *text_view;
	GtkTextBuffer        *text_buffer;
};

G_DEFINE_FINAL_TYPE (EchoWindow, echo_window, ADW_TYPE_APPLICATION_WINDOW)

static void
echo_window_class_init (EchoWindowClass *klass)
{
	GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

	gtk_widget_class_set_template_from_resource (widget_class, "/app/drey/Echo/echo-window.ui");
	gtk_widget_class_bind_template_child (widget_class, EchoWindow, header_bar);
	gtk_widget_class_bind_template_child (widget_class, EchoWindow, text_view);
	gtk_widget_class_bind_template_child (widget_class, EchoWindow, text_buffer);
}

static void
echo_window_init (EchoWindow *self)
{
	gtk_widget_init_template (GTK_WIDGET (self));

#if ECHO_DEVELOP
  gtk_widget_add_css_class (GTK_WIDGET (self), "devel");
#endif

  // Sample ELF disassembly to get a feel for where we're headed.
  //
  void
  sample (EchoWindow *self);
  sample (self);
}

#include <LIEF/LIEF.hpp>
#include <Zydis/Zydis.h>
#include <Zycore/Format.h>

void
sample (EchoWindow *self)
{
  using namespace std;
  using namespace LIEF::ELF;

  ZydisDecoder decoder;
  ZydisDecoderInit(&decoder, ZYDIS_MACHINE_MODE_LONG_64, ZYDIS_STACK_WIDTH_64);
  ZydisFormatter fmt;
  ZydisFormatterInit(&fmt, ZYDIS_FORMATTER_STYLE_INTEL);
  ZydisDecodedInstruction instr;
  ZydisDecodedOperand operands[ZYDIS_MAX_OPERAND_COUNT];

  auto elf = Parser::parse ("/home/wroy/Documents/sample");
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

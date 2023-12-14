// libecho/echo.hxx
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

#include <adwaita.h>
#include <libpeas.h>

#include <memory> // < default_delete

namespace std
{
  template <>
  struct default_delete <PeasPluginInfo>
  {
    void
    operator() (auto p) noexcept
    {
      if (p != nullptr)
        g_object_unref (p);
    }
  };

  template <>
  struct default_delete <GAsyncQueue>
  {
    void
    operator() (auto p) noexcept
    {
      if (p != nullptr)
        g_async_queue_unref (p);
    }
  };

  template <>
  struct default_delete <GBookmarkFile>
  {
    void
    operator() (auto p) noexcept
    {
      if (p != nullptr)
        g_bookmark_file_free (p);
    }
  };

  template <>
  struct default_delete <GBytes>
  {
    void
    operator() (auto p) noexcept
    {
      if (p != nullptr)
        g_bytes_unref (p);
    }
  };

  template <>
  struct default_delete <GChecksum>
  {
    void
    operator() (auto p) noexcept
    {
      if (p != nullptr)
        g_checksum_free (p);
    }
  };

  template <>
  struct default_delete <GDateTime>
  {
    void
    operator() (auto p) noexcept
    {
      if (p != nullptr)
        g_date_time_unref (p);
    }
  };

  template <>
  struct default_delete <GDir>
  {
    void
    operator() (auto p) noexcept
    {
      if (p != nullptr)
        g_dir_close (p);
    }
  };

  template <>
  struct default_delete <GError>
  {
    void
    operator() (auto p) noexcept
    {
      if (p != nullptr)
        g_error_free (p);
    }
  };

  template <>
  struct default_delete <GHashTable>
  {
    void
    operator() (auto p) noexcept
    {
      if (p != nullptr)
        g_hash_table_unref (p);
    }
  };

  template <>
  struct default_delete <GHmac>
  {
    void
    operator() (auto p) noexcept
    {
      if (p != nullptr)
        g_hmac_unref (p);
    }
  };

  template <>
  struct default_delete <GIOChannel>
  {
    void
    operator() (auto p) noexcept
    {
      if (p != nullptr)
        g_io_channel_unref (p);
    }
  };

  template <>
  struct default_delete <GKeyFile>
  {
    void
    operator() (auto p) noexcept
    {
      if (p != nullptr)
        g_key_file_unref (p);
    }
  };

  template <>
  struct default_delete <GList>
  {
    void
    operator() (auto p) noexcept
    {
      if (p != nullptr)
        g_list_free (p);
    }
  };

  template <>
  struct default_delete <GArray>
  {
    void
    operator() (auto p) noexcept
    {
      if (p != nullptr)
        g_array_unref (p);
    }
  };

  template <>
  struct default_delete <GPtrArray>
  {
    void
    operator() (auto p) noexcept
    {
      if (p != nullptr)
        g_ptr_array_unref (p);
    }
  };

  template <>
  struct default_delete <GByteArray>
  {
    void
    operator() (auto p) noexcept
    {
      if (p != nullptr)
        g_byte_array_unref (p);
    }
  };

  template <>
  struct default_delete <GMainContext>
  {
    void
    operator() (auto p) noexcept
    {
      if (p != nullptr)
        g_main_context_unref (p);
    }
  };

  template <>
  struct default_delete <GMainLoop>
  {
    void
    operator() (auto p) noexcept
    {
      if (p != nullptr)
        g_main_loop_unref (p);
    }
  };

  template <>
  struct default_delete <GSource>
  {
    void
    operator() (auto p) noexcept
    {
      if (p != nullptr)
        g_source_unref (p);
    }
  };

  template <>
  struct default_delete <GMappedFile>
  {
    void
    operator() (auto p) noexcept
    {
      if (p != nullptr)
        g_mapped_file_unref (p);
    }
  };

  template <>
  struct default_delete <GMarkupParseContext>
  {
    void
    operator() (auto p) noexcept
    {
      if (p != nullptr)
        g_markup_parse_context_unref (p);
    }
  };

  template <>
  struct default_delete <GNode>
  {
    void
    operator() (auto p) noexcept
    {
      if (p != nullptr)
        g_node_destroy (p);
    }
  };

  template <>
  struct default_delete <GOptionContext>
  {
    void
    operator() (auto p) noexcept
    {
      if (p != nullptr)
        g_option_context_free (p);
    }
  };

  template <>
  struct default_delete <GOptionGroup>
  {
    void
    operator() (auto p) noexcept
    {
      if (p != nullptr)
        g_option_group_unref (p);
    }
  };

  template <>
  struct default_delete <GPatternSpec>
  {
    void
    operator() (auto p) noexcept
    {
      if (p != nullptr)
        g_pattern_spec_free (p);
    }
  };

  template <>
  struct default_delete <GQueue>
  {
    void
    operator() (auto p) noexcept
    {
      if (p != nullptr)
        g_qeue_free (p);
    }
  };

  template <>
  struct default_delete <GRand>
  {
    void
    operator() (auto p) noexcept
    {
      if (p != nullptr)
        g_rand_free (p);
    }
  };

  template <>
  struct default_delete <GRegex>
  {
    void
    operator() (auto p) noexcept
    {
      if (p != nullptr)
        g_regex_unref (p);
    }
  };

  template <>
  struct default_delete <GMatchInfo>
  {
    void
    operator() (auto p) noexcept
    {
      if (p != nullptr)
        g_match_info_unref (p);
    }
  };

  template <>
  struct default_delete <GScanner>
  {
    void
    operator() (auto p) noexcept
    {
      if (p != nullptr)
        g_scanner_destroy (p);
    }
  };

  template <>
  struct default_delete <GSequence>
  {
    void
    operator() (auto p) noexcept
    {
      if (p != nullptr)
        g_sequence_free (p);
    }
  };

  template <>
  struct default_delete <GSList>
  {
    void
    operator() (auto p) noexcept
    {
      if (p != nullptr)
        g_slist_free (p);
    }
  };

  template <>
  struct default_delete <GString>
  {
    void
    operator() (auto p) noexcept
    {
      if (p != nullptr)
        g_autoptr_cleanup_gstring_free (p);
    }
  };

  template <>
  struct default_delete <GStringChunk>
  {
    void
    operator() (auto p) noexcept
    {
      if (p != nullptr)
        g_string_chunk_free (p);
    }
  };

  template <>
  struct default_delete <GThread>
  {
    void
    operator() (auto p) noexcept
    {
      if (p != nullptr)
        g_thread_unref (p);
    }
  };

  template <>
  struct default_delete <GMutex>
  {
    void
    operator() (auto p) noexcept
    {
      if (p != nullptr)
        g_mutex_clear (p);
    }
  };

  template <>
  struct default_delete <GCond>
  {
    void
    operator() (auto p) noexcept
    {
      if (p != nullptr)
        g_cond_clear (p);
    }
  };

  template <>
  struct default_delete <GTimer>
  {
    void
    operator() (auto p) noexcept
    {
      if (p != nullptr)
        g_timer_destroy (p);
    }
  };

  template <>
  struct default_delete <GTimeZone>
  {
    void
    operator() (auto p) noexcept
    {
      if (p != nullptr)
        g_time_zone_unref (p);
    }
  };

  template <>
  struct default_delete <GTree>
  {
    void
    operator() (auto p) noexcept
    {
      if (p != nullptr)
        g_tree_unref (p);
    }
  };

  template <>
  struct default_delete <GVariant>
  {
    void
    operator() (auto p) noexcept
    {
      if (p != nullptr)
        g_variant_unref (p);
    }
  };

  template <>
  struct default_delete <GVariantBuilder>
  {
    void
    operator() (auto p) noexcept
    {
      if (p != nullptr)
        g_variant_builder_unref (p);
    }
  };

  template <>
  struct default_delete <GVariantIter>
  {
    void
    operator() (auto p) noexcept
    {
      if (p != nullptr)
        g_variant_iter_free (p);
    }
  };

  template <>
  struct default_delete <GVariantDict>
  {
    void
    operator() (auto p) noexcept
    {
      if (p != nullptr)
        g_variant_dict_unref (p);
    }
  };

  template <>
  struct default_delete <GVariantType>
  {
    void
    operator() (auto p) noexcept
    {
      if (p != nullptr)
        g_variant_type_free (p);
    }
  };

  template <>
  struct default_delete <gchar>
  {
    void
    operator() (auto p) noexcept
    {
      if (p != nullptr)
        g_free (p);
    }
  };

  using gcharv = gchar *;
  template <>
  struct default_delete <gcharv>
  {
    void
    operator() (auto p) noexcept
    {
      if (p != nullptr)
        g_strfreev (p);
    }
  };
}

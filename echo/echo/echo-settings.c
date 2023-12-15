/* echo-settings.c
 *
 * Copyright 2023 William Roy
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

#include <echo/echo-settings.h>

struct _EchoSettings
{
  GObject    parent_instance;
  GSettings *settings;
};

enum
{
  PROP_0,
  PROP_STYLE_VARIANT,
  N_PROPS
};

G_DEFINE_FINAL_TYPE (EchoSettings, echo_settings, G_TYPE_OBJECT)

static GParamSpec *properties[N_PROPS];

EchoSettings *
echo_settings_new ()
{
  const auto self = g_object_new (ECHO_TYPE_SETTINGS, nullptr);

  return ECHO_SETTINGS (self);
}

static void
echo_settings_dispose (GObject *object)
{
  const auto self = ECHO_SETTINGS (object);

  g_assert (ECHO_IS_SETTINGS (self));

  g_clear_object (&self->settings);

  G_OBJECT_CLASS (echo_settings_parent_class)->dispose (object);
}

AdwColorScheme
echo_settings_get_style_variant (EchoSettings *self)
{
  g_assert (ECHO_IS_SETTINGS (self));

  return g_settings_get_enum (self->settings, "style-variant");
}

static void
echo_settings_get_property (GObject    *object,
                            guint       prop_id,
                            GValue     *value,
                            GParamSpec *pspec)
{
  const auto self = ECHO_SETTINGS (object);

  g_assert (ECHO_IS_SETTINGS (self));

  switch (prop_id)
    {
    case PROP_STYLE_VARIANT:
      g_value_set_enum (value, echo_settings_get_style_variant (self));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

void
echo_settings_set_style_variant (EchoSettings  *self,
                                 AdwColorScheme color_scheme)
{
  g_assert (ECHO_IS_SETTINGS (self));
  g_assert (color_scheme == ADW_COLOR_SCHEME_DEFAULT
            || color_scheme == ADW_COLOR_SCHEME_FORCE_LIGHT
            || color_scheme == ADW_COLOR_SCHEME_FORCE_DARK);

  g_settings_set_enum (self->settings, "style-variant", color_scheme);
}

static void
echo_settings_set_property (GObject      *object,
                            guint         prop_id,
                            const GValue *value,
                            GParamSpec   *pspec)
{
  const auto self = ECHO_SETTINGS (object);

  g_assert (ECHO_IS_SETTINGS (self));

  switch (prop_id)
    {
    case PROP_STYLE_VARIANT:
      echo_settings_set_style_variant (self, g_value_get_enum (value));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
echo_settings_class_init (EchoSettingsClass *klass)
{
  const auto object_class = G_OBJECT_CLASS (klass);

  object_class->dispose      = echo_settings_dispose;
  object_class->get_property = echo_settings_get_property;
  object_class->set_property = echo_settings_set_property;

  properties[PROP_STYLE_VARIANT] =
    g_param_spec_enum ("style-variant",
                       nullptr, nullptr,
                       ADW_TYPE_COLOR_SCHEME,
                       ADW_COLOR_SCHEME_DEFAULT,
                       G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

  g_object_class_install_properties (object_class, N_PROPS, properties);
}

static void
echo_settings_changed_cb (EchoSettings *self,
                          const char   *key,
                          GSettings    *settings)
{
  g_assert (ECHO_IS_SETTINGS (self));
  g_assert (key != nullptr);
  g_assert (G_IS_SETTINGS (settings));

  if (g_str_equal (key, "style-variant"))
    g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_STYLE_VARIANT]);
}

static void
echo_settings_init (EchoSettings *self)
{
  self->settings = g_settings_new ("app.drey.Echo");

  g_signal_connect_object (self->settings, "changed",
                           G_CALLBACK (echo_settings_changed_cb),
                           self,
                           G_CONNECT_SWAPPED);
}

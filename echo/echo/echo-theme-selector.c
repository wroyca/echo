/* echo-theme-selector.c
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

#include <echo/echo-theme-selector.h>

struct _EchoThemeSelector
{
  GtkWidget        parent_instance;

  GtkWidget       *box;
  GtkToggleButton *dark;
  GtkToggleButton *light;
  GtkToggleButton *follow;

  char            *action_name;
};

enum
{
  PROP_0,
  PROP_ACTION_NAME,
  N_PROPS
};

G_DEFINE_TYPE (EchoThemeSelector, echo_theme_selector, GTK_TYPE_WIDGET)

static GParamSpec *properties[N_PROPS];

EchoThemeSelector *
echo_theme_selector_new ()
{
  const auto self = g_object_new (ECHO_TYPE_THEME_SELECTOR, nullptr);

  return ECHO_THEME_SELECTOR (self);
}

static void
echo_theme_selector_dispose (GObject *object)
{
  const auto self = ECHO_THEME_SELECTOR (object);

  g_assert (ECHO_IS_THEME_SELECTOR (self));

  g_clear_pointer (&self->box, gtk_widget_unparent);
  g_clear_pointer (&self->action_name, g_free);

  G_OBJECT_CLASS (echo_theme_selector_parent_class)->dispose (object);
}

const char *
echo_theme_selector_get_action_name (EchoThemeSelector *self)
{
  g_assert (ECHO_IS_THEME_SELECTOR (self));

  return self->action_name;
}

void
echo_theme_selector_set_action_name (EchoThemeSelector *self,
                                     const char        *action_name)
{
  g_assert (ECHO_IS_THEME_SELECTOR (self));

  if (g_strcmp0 (action_name, self->action_name) == 0)
    return;

  g_free (self->action_name);

  self->action_name = g_strdup (action_name);

  gtk_actionable_set_action_name (GTK_ACTIONABLE (self->dark), action_name);
  gtk_actionable_set_action_name (GTK_ACTIONABLE (self->light), action_name);
  gtk_actionable_set_action_name (GTK_ACTIONABLE (self->follow), action_name);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_ACTION_NAME]);
}

static void
echo_theme_selector_get_property (GObject    *object,
                                  guint       prop_id,
                                  GValue     *value,
                                  GParamSpec *pspec)
{
  const auto self = ECHO_THEME_SELECTOR (object);

  g_assert (ECHO_IS_THEME_SELECTOR (self));

  switch (prop_id)
    {
    case PROP_ACTION_NAME:
      g_value_set_string (value, echo_theme_selector_get_action_name (self));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
echo_theme_selector_set_property (GObject      *object,
                                  guint         prop_id,
                                  const GValue *value,
                                  GParamSpec   *pspec)
{
  const auto self = ECHO_THEME_SELECTOR (object);

  g_assert (ECHO_IS_THEME_SELECTOR (self));

  switch (prop_id)
    {
    case PROP_ACTION_NAME:
      echo_theme_selector_set_action_name (self, g_value_get_string (value));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
echo_theme_selector_class_init (EchoThemeSelectorClass *klass)
{
  const auto object_class = G_OBJECT_CLASS (klass);
  const auto widget_class = GTK_WIDGET_CLASS (klass);
  const auto resource = "/app/drey/Echo/echo-theme-selector.ui";

  object_class->dispose      = echo_theme_selector_dispose;
  object_class->get_property = echo_theme_selector_get_property;
  object_class->set_property = echo_theme_selector_set_property;

  properties[PROP_ACTION_NAME] =
    g_param_spec_string ("action-name",
                         nullptr, nullptr, nullptr,
                         G_PARAM_READWRITE |
                         G_PARAM_EXPLICIT_NOTIFY |
                         G_PARAM_STATIC_STRINGS);

  g_object_class_install_properties (object_class, N_PROPS, properties);

  gtk_widget_class_set_css_name (widget_class, "themeselector");
  gtk_widget_class_set_template_from_resource (widget_class, resource);
  gtk_widget_class_set_layout_manager_type (widget_class, GTK_TYPE_BIN_LAYOUT);

  gtk_widget_class_bind_template_child (widget_class, EchoThemeSelector, box);
  gtk_widget_class_bind_template_child (widget_class, EchoThemeSelector, dark);
  gtk_widget_class_bind_template_child (widget_class, EchoThemeSelector, light);
  gtk_widget_class_bind_template_child (widget_class, EchoThemeSelector, follow);
}

static void
on_notify_system_supports_color_schemes_cb (EchoThemeSelector *self,
                                            GParamSpec        *pspec,
                                            AdwStyleManager   *style_manager)
{
  g_assert (ECHO_IS_THEME_SELECTOR (self));
  g_assert (ADW_IS_STYLE_MANAGER (style_manager));

  const auto visible
      = adw_style_manager_get_system_supports_color_schemes (style_manager);
  gtk_widget_set_visible (GTK_WIDGET (self->follow), visible);
}

static void
on_notify_dark_cb (EchoThemeSelector *self,
                   GParamSpec        *pspec,
                   AdwStyleManager   *style_manager)
{
  g_assert (ECHO_IS_THEME_SELECTOR (self));
  g_assert (ADW_IS_STYLE_MANAGER (style_manager));

  style_manager = adw_style_manager_get_default ();

  if (adw_style_manager_get_dark (style_manager))
    gtk_widget_add_css_class (GTK_WIDGET (self), "dark");
  else
    gtk_widget_remove_css_class (GTK_WIDGET (self), "dark");
}

static void
echo_theme_selector_init (EchoThemeSelector *self)
{
  gtk_widget_init_template (GTK_WIDGET (self));

  const auto style_manager = adw_style_manager_get_default ();
  const auto dark = adw_style_manager_get_dark (style_manager);

  g_signal_connect_object (style_manager,
                           "notify::system-supports-color-schemes",
                           G_CALLBACK (on_notify_system_supports_color_schemes_cb),
                           self,
                           G_CONNECT_SWAPPED);
  g_signal_connect_object (style_manager,
                           "notify::dark",
                           G_CALLBACK (on_notify_dark_cb),
                           self,
                           G_CONNECT_SWAPPED);

  self->action_name = g_strdup (dark ? "dark" : "light");

  on_notify_system_supports_color_schemes_cb (self, nullptr, style_manager);
  on_notify_dark_cb (self, nullptr, style_manager);
}

// src/pingus/components/button_panel.cpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 1999 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#include "pingus/components/button_panel.hpp"

#include <algorithm>

#include "engine/display/drawing_context.hpp"
#include "pingus/fonts.hpp"
#include "pingus/globals.hpp"
#include "pingus/server.hpp"
#include "util/string_util.hpp"

namespace pingus {

namespace {

// The widest action icon ends 36 pixels in, so counts start just past it.
const int TEXT_X = 40;
const int TEXT_PADDING = 6;
const int TIP_GAP = 6;

} // namespace


ButtonPanel::ButtonPanel(Server* s, const Vector2i& pos) :
  RectComponent(Rect()),
  server(s),
  background("core/buttons/buttonbackground"),
  highlight("core/buttons/buttonbackgroundhl"),
  buttons(),
  current_button(0),
  show_tip(false),
  tip_button(0)
{
  ActionHolder* aholder = server->get_action_holder();

  std::vector<ActionName::Enum> actions = aholder->get_available_actions();

  set_rect(Rect(Vector2i(pos.x, pos.y - (static_cast<int>(actions.size()) * 38)/2),
                Size(60, static_cast<int>(actions.size()) * 38)));

  // Sort the action so that they always have the same order in the panel
  std::sort(actions.begin(), actions.end());

  for(std::vector<ActionName::Enum>::size_type i = 0; i < actions.size(); ++i)
  {
    ActionButton button;
    button.name   = actions[i];
    button.sprite = Sprite("pingus/player0/" + ActionName::to_string(button.name) + "/right");
    button.sprite.set_hotspot(origin_center, 0, 0);
    button.sprite.set_play_loop(true);
    buttons.push_back(button);
  }
}

ButtonPanel::~ButtonPanel()
{
}

void
ButtonPanel::draw(DrawingContext& gc)
{
  for(std::vector<ActionButton>::size_type i = 0; i < buttons.size(); ++i)
  {
    const int y = rect.top + 38*static_cast<int>(i);
    const std::string str = count_text(buttons[i].name);
    const int width = text_width(str);

    // Stretched only when the count needs more room than the button has.
    const Sprite& back = (current_button == i) ? highlight : background;
    if (width > back.get_width())
      gc.draw(back, Vector2i(rect.left, y), Size(width, back.get_height()));
    else
      gc.draw(back, Vector2i(rect.left, y));

    gc.draw(buttons[i].sprite, Vector2i(rect.left + 20, y + 16));

    gc.print_left(fonts::pingus_small, Vector2i(rect.left + TEXT_X, y + 5), str);

    if (show_tip && tip_button == i)
    {
      gc.print_left(fonts::pingus_small,
                    Vector2i(rect.left + std::max(width, back.get_width()) + TIP_GAP, y + 5),
                    ActionName::to_screenname(buttons[i].name));
    }
  }
}

std::string
ButtonPanel::count_text(ActionName::Enum name) const
{
  ActionHolder* aholder = server->get_action_holder();

  if (globals::developer_mode)
  {
    std::ostringstream out;
    out << aholder->get_available(name) << " / " << aholder->get_used(name);
    return out.str();
  }

  return StringUtil::to_string(aholder->get_available(name));
}

int
ButtonPanel::text_width(const std::string& str) const
{
  return TEXT_X + static_cast<int>(fonts::pingus_small.get_width(str)) + TEXT_PADDING;
}

void
ButtonPanel::update (float delta)
{
  // The panel takes clicks across the widest button.
  int width = background.get_width();
  for (const auto& button : buttons)
    width = std::max(width, text_width(count_text(button.name)));
  rect.right = rect.left + width;

  for(std::vector<ActionButton>::size_type i = 0; i < buttons.size(); ++i)
    if (i == current_button)
      buttons[i].sprite.update(delta);
    else
      buttons[i].sprite.set_frame(0);
}

ActionName::Enum
ButtonPanel::get_action_name()
{
  if (!buttons.empty())
  {
    return buttons[current_button].name;
  }
  // No actions available
  return ActionName::WALKER;
}

void
ButtonPanel::set_button(int n)
{
  if (n >= 0 || n < static_cast<int>(buttons.size()-1))
  {
    current_button = n;
  }
  else
  {
    // FIXME: Play 'boing' sound here
  }
}

void
ButtonPanel::next_action()
{
  if (!buttons.empty())
  {
    current_button = (current_button + 1 + int(buttons.size())) % int(buttons.size());
  }
}

void
ButtonPanel::previous_action()
{
  if (!buttons.empty())
  {
    current_button = (current_button - 1 + int(buttons.size())) % int(buttons.size());
  }
}

void
ButtonPanel::on_primary_button_press(int /*x*/, int y)
{
  int action = (y - rect.top) / 38;
  current_button = static_cast<size_t>(std::clamp(action, 0, int(buttons.size()-1)));
}

void
ButtonPanel::on_primary_button_release(int /*x*/, int /*y*/)
{
}

void
ButtonPanel::on_pointer_enter()
{
  show_tip = true;
}

void
ButtonPanel::on_pointer_leave()
{
  show_tip = false;
}

void
ButtonPanel::on_pointer_move(int /*x*/, int y)
{
  int action = (y - rect.top) / 38;
  tip_button = static_cast<size_t>(std::clamp(action, 0, int(buttons.size()-1)));
}

void
ButtonPanel::set_pos(const Vector2i& pos)
{
  set_rect(Rect(Vector2i(pos.x, pos.y - (static_cast<int>(buttons.size()) * 38)/2),
                Size(60, static_cast<int>(buttons.size()) * 38)));
}


} // namespace pingus

// EOF

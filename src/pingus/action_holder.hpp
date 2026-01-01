// src/pingus/action_holder.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 1999 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_PINGUS_ACTION_HOLDER_HPP
#define HEADER_PINGUS_PINGUS_ACTION_HOLDER_HPP

#include <map>
#include <vector>

#include "pingus/action_name.hpp"

class PingusLevel;
class PinguAction;

/**
 * The ActionHolder is the backend of the ButtonPanel. It is responsible for
 * creating new PinguActions and (if necessary) restricting the number of
 * actions that can be created.
 *
 */
class ActionHolder
{
private:
  struct ActionCount
  {
    int available;
    int used;
  };

  /** A map holding the number of available actions.
   *  For each action <i>name</i> there is a map (<i>name</i>, <i>n</i>)
   *  where the integer <i>n</i> indicates how much more actions
   *  called <i>name</i> can be created.
   */
  std::map<ActionName::Enum, ActionCount> m_actions;

public:
  /** Create an action holder from the number of actions given in a
      Pingus Level file */
  ActionHolder(const PingusLevel& plf);
  ~ActionHolder();

  /** @return a list of available actions in the current level */
  std::vector<ActionName::Enum> get_available_actions();

  /** Sets the number of actions, which are available in the pool.
   * @param name the name of the action
   * @param available the number of actions available
   */
  void set_actions(ActionName::Enum name, int available);

  /** Adds an action to the pool of actions, making one more action available
   * @param name the name of the action
   */
  void push_action (ActionName::Enum name);

  /** Removes an action from the pool of actions
      @return true if an action was available and removed, false if no
      actions where available */
  bool pop_action (ActionName::Enum name);

  /** Returns the number of actions of the specified name which are available
      thru get_action()

      @return 0 if the name is unknown */
  int get_available(ActionName::Enum name);
  int get_used(ActionName::Enum name);

private:
  ActionHolder (const ActionHolder&);
  ActionHolder& operator= (const ActionHolder&);
};

#endif

// EOF

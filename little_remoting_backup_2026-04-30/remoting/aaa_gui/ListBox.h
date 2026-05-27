// Copyright (C) 2008,2009,2010,2011,2012 GlavSoft LLC.
// All rights reserved.
//
//-------------------------------------------------------------------------
// This file is part of the T i g h t V N C software.  Please visit our Web site:
//
//                       http://www.t i g h t v n c.com/
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, w_rite to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//-------------------------------------------------------------------------
//

#pragma once


#include "innate_subsystem/gui/Window.h"
//////#include "subsystem/platform/::string.h"

class CLASS_DECL_REMOTING ListBox : public ::innate_subsystem::Control
{
public:
  ListBox();
  ~ListBox();
public:
  void addString(const ::scoped_string & scopedstrStr);
  void addString(const ::scoped_string & scopedstrStr, void *tag);
  ::string getItemText(::i32 index);
  void setItemText(::i32 index, const ::scoped_string & scopedstrStr);
  void insertString(::i32 index, const ::scoped_string & scopedstrStr);
  void insertString(::i32 index, const ::scoped_string & scopedstrStr, ::lparam data);
  void appendString(const ::scoped_string & scopedstrStr, ::lparam data);
  void setItemData(::i32 index, ::lparam data);
  void removeString(::i32 index);
  ::i32 getSelectedIndex();
  ::i32 getTopIndex();
  void setTopIndex(::i32 index);
  void setSelectedIndex(::i32 index);
  ::lparam getItemData(::i32 index);
  ::i32 getCount();
  void clear();
};



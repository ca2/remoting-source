// Copyright (C) 2009,2010,2011,2012 GlavSoft LLC.
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


#include "subsystem/_common_header.h"
#include "innate_subsystem/gui/Window.h"

class CLASS_DECL_REMOTING ComboBox : public ::innate_subsystem::Control
{
public:
  ComboBox();
  ~ComboBox();

  // Adds new item to the end of combo box items ::list_base.
  ::i32 addItem(const ::scoped_string & scopedstrText);

  // Adds new item to the end of combo box items ::list_base.
  ::i32 addItem(const ::scoped_string & scopedstrText, void *tag);

  // Inserts new item to the specified pointPosition
  void insertItem(::i32 index, const ::scoped_string & scopedstrText);

  // Inserts new item to the specified pointPosition
  void insertItem(::i32 index, const ::scoped_string & scopedstrText, void *tag);

  // Returns count of combo box items
  ::i32 getItemsCount() const;

  // Sets user data (tag) associated with combo box item with specified index
  void setItemData(::i32 index, void *tag);

  // Returns user data associated with combo box item with specified index
  void *getItemData(::i32 index) const;

  // Sets text associated with combo box item with specified index
  ::string getItemText(::i32 index) const;

  // Returns current selected item index
  ::i32 getSelectedItemIndex();

  // Selects item with specified index
  void setSelectedItem(::i32 index);

  // Deletes item from specified location
  void deleteItem(::i32 index);

  // Removes all combo box items
  void removeAllItems();
};



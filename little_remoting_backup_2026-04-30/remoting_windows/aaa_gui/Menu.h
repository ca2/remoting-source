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
//#include aaa_<crtdbg.h>

class CLASS_DECL_REMOTING Menu
{
public:
  Menu();
  virtual ~Menu();

  HMENU getMenu();
  void setMenu(HMENU hmenu);
  bool getWindowMenu(const ::operating_system::window & operatingsystemwindow);
  void getSystemMenu(const ::operating_system::window & operatingsystemwindow);
  void create();
  bool loadMenu(LPCTSTR lpMenuName);
  void createPopupMenu();
  bool getSubMenu(::i32 nPos, Menu *menu);
  void termMenu();
  
  ::i32 getMenuItemCount();
  bool appendMenu(const ::scoped_string & strVal, ::u32 uID);
  bool appendSeparator();
  bool appendSubMenu(const ::scoped_string &  strVal, Menu *pMenu);

  bool insertMenuItem(::u32 uItem, const ::scoped_string &  strVal, ::u32 uID);
  bool insertCheckMenuItem(::u32 uItem, const ::scoped_string &  strVal, ::u32 uID);
  bool insertSeparator(::u32 uItem);
  bool insertSubMenu(::u32 uItem, const ::scoped_string &  strVal, Menu *pMenu);

  bool enableMenuItem(::u32 uID, ::u32 uEnable);
  bool checkedMenuItem(::u32 uID, bool bEnable);
  bool deleteMenu(::u32 uPosition);

  ::i32 findMenuItem(::u32 uID);

  bool setDefaultItem(::u32 uID);

  void operator= (HMENU hmenu)
  {
    setMenu(hmenu);
  }

//private:
  bool appendMenu(::u32 uFlags, UINT_PTR uIDNewItem, const ::scoped_string & scopedstrNewItem);
  bool insertMenuItem(::u32 uItem, bool fByPosition, LPCMENUITEMINFO lpmii);
  bool modifyMenu(::u32 uPosition, ::u32 uFlags, LONG_PTR uIDNewItem, LPCTSTR lpNewItem);
  bool setMenuItem(::u32 uItem, bool fByPosition, LPMENUITEMINFO lpmii);

//protected:
  HMENU m_menu;
  bool m_bCreated;
};



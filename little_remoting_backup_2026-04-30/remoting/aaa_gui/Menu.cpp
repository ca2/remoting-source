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
#include "framework.h"
#include "Menu.h"

Menu::Menu()
: m_menu(0),
  m_bCreated(false)
{
}

HMENU Menu::getMenu()
{
  return m_menu;
}

void Menu::setMenu(HMENU hmenu)
{
  _ASSERT(m_menu == 0);

  m_menu = hmenu;
}

bool Menu::getWindowMenu(const ::operating_system::window & operatingsystemwindow)
{
  _ASSERT(m_menu == 0);

  m_menu = GetMenu(hwnd);
  return (m_menu == 0 ? false : true);
}

void Menu::getSystemMenu(const ::operating_system::window & operatingsystemwindow)
{
  _ASSERT(m_menu == 0);

  m_menu = GetSystemMenu(hwnd, false);
}

void Menu::create()
{
  _ASSERT(m_menu == 0);

  m_menu = CreateMenu();
  m_bCreated = true;
}

bool Menu::loadMenu(LPCTSTR lpMenuName)
{
  _ASSERT(m_menu == 0);

  m_menu = LoadMenu(GetModuleHandle(0), lpMenuName);
  m_bCreated = true;
  return (!m_menu?false:true);
}

void Menu::createPopupMenu()
{
  _ASSERT(m_menu == 0);

  m_menu = CreatePopupMenu();
  m_bCreated = true;
}

::i32 Menu::getMenuItemCount()
{
  _ASSERT(m_menu != 0);

  return GetMenuItemCount(m_menu);
}

bool Menu::appendMenu(::u32 uFlags, UINT_PTR uIDNewItem, const ::scoped_string & scopedstrNewItem)
{
  _ASSERT(m_menu != 0);

  return !!AppendMenu(m_menu, uFlags, uIDNewItem, ::wstring(scopedstrNewItem).c_str());
}

bool Menu::insertMenuItem(::u32 uItem, bool fByPosition, LPCMENUITEMINFO lpmii)
{
  _ASSERT(m_menu != 0);

  return !!InsertMenuItem(m_menu, uItem, fByPosition, lpmii);
}

bool Menu::modifyMenu(::u32 uPosition, ::u32 uFlags, LONG_PTR uIDNewItem, LPCTSTR lpNewItem)
{
  _ASSERT(m_menu != 0);

  return !!ModifyMenu(m_menu, uPosition, uFlags, uIDNewItem, lpNewItem);
}

bool Menu::deleteMenu(::u32 uPosition)
{
  _ASSERT(m_menu != 0);

  return !!DeleteMenu(m_menu, uPosition, MF_BYPOSITION);
}

bool Menu::getSubMenu(::i32 nPos, Menu *menu)
{
  HMENU tmenu;

  _ASSERT(m_menu != 0 && menu);
  tmenu = GetSubMenu(m_menu, nPos);
  if (tmenu) {
    menu->setMenu(tmenu);
  }
  return (!tmenu?false:true);
}

bool Menu::enableMenuItem(::u32 uID, ::u32 uEnable)
{
  _ASSERT(m_menu != 0);

  return !!EnableMenuItem(m_menu, uID, uEnable);
}

bool Menu::setMenuItem(::u32 uItem, bool fByPosition, LPMENUITEMINFO lpmii)
{
  _ASSERT(m_menu != 0);

  return !!SetMenuItemInfo(m_menu, uItem, fByPosition, lpmii);
}

void Menu::termMenu()
{
  if (m_menu && m_bCreated) {
    DestroyMenu(m_menu);
  }
  m_menu = 0;
  m_bCreated = false;
}

Menu::~Menu()
{
  if (m_menu && m_bCreated) {
    DestroyMenu(m_menu);
  }
}

::i32 Menu::findMenuItem(::u32 uID)
{
  _ASSERT(m_menu != 0);

  for (::i32 i = 0; i < getMenuItemCount(); i++) {
    if (GetMenuItemID(m_menu, i) == uID) {
      return i;
    }
  }
  return -1;
}

bool Menu::appendMenu(const ::scoped_string & scopedstrData, ::u32 uID)
{
  return appendMenu(MF_STRING, uID, scopedstrData);
}

bool Menu::appendSeparator()
{
  return appendMenu(MF_MENUBREAK, 0, 0);
}

bool Menu::appendSubMenu(const ::scoped_string & scopedstrData, Menu *pMenu)
{
  return appendMenu(MF_POPUP, (UINT_PTR)pMenu->getMenu(), scopedstrData);
}

bool Menu::insertMenuItem(::u32 uItem, const ::scoped_string & scopedstrData, ::u32 uID)
{
  MENUITEMINFO mii;

   ::wstring wstrData(scopedstrData);

  ZeroMemory(&mii, sizeof(MENUITEMINFO));
  mii.cbSize = sizeof(MENUITEMINFO);
  mii.fMask = MIIM_STRING | MIIM_ID;
  mii.dwTypeData = (LPTSTR)wstrData.c_str();
  mii.fState = MFS_DEFAULT; 
  mii.wID = uID;
  return insertMenuItem(uItem, true, (LPMENUITEMINFO)&mii);
}

bool Menu::insertCheckMenuItem(::u32 uItem, const ::scoped_string & scopedstrData, ::u32 uID)
{
  MENUITEMINFO mii;
::wstring wstrData(scopedstrData);
  ZeroMemory(&mii, sizeof(MENUITEMINFO));
  mii.cbSize = sizeof(MENUITEMINFO);
  mii.fMask = MIIM_STRING | MIIM_ID | MIIM_STATE;
  mii.dwTypeData = (LPTSTR)wstrData.c_str();
  mii.fState = MFS_UNCHECKED; 
  mii.wID = uID;
  return insertMenuItem(uItem, true, (LPMENUITEMINFO)&mii);
}

bool Menu::checkedMenuItem(::u32 uID, bool bEnable)
{
  _ASSERT(m_menu != 0);

  ::i32 pos = findMenuItem(uID);
  if (pos == -1) {
    return false;
  }
  ::u32 command = bEnable ? MF_CHECKED : MF_UNCHECKED;
  DWORD res = CheckMenuItem(m_menu, pos, MF_BYPOSITION | command);
  return (res == -1) ? false : true;
}

bool Menu::insertSeparator(::u32 uItem)
{
  MENUITEMINFO mii;

  ZeroMemory(&mii, sizeof(MENUITEMINFO));
  mii.cbSize = sizeof(MENUITEMINFO);
  mii.fType = MFT_SEPARATOR;
  return insertMenuItem(uItem, true, (LPMENUITEMINFO)&mii);
}

bool Menu::insertSubMenu(::u32 uItem, const ::scoped_string & scopedstrData, Menu *pMenu)
{
  MENUITEMINFO mii;

  ZeroMemory(&mii, sizeof(MENUITEMINFO));
  mii.cbSize = sizeof(MENUITEMINFO);
  mii.fMask = MIIM_SUBMENU;
  mii.hSubMenu = pMenu->getMenu();
  return insertMenuItem(uItem, true, (LPMENUITEMINFO)&mii);
}

bool Menu::setDefaultItem(::u32 uID)
{
  _ASSERT(m_menu != 0);

  return !!SetMenuDefaultItem(m_menu, uID, false);
}

// Copyright (C) 2011,2012 GlavSoft LLC.
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

// ScrollBar class
// This class doesn't create any window, it only show/hide that is already
// contained in existed window.

class CLASS_DECL_REMOTING ScrollBar
{
public:
  ScrollBar();

  void setWindow(const ::operating_system::window & operatingsystemwindow);
  bool showVertScroll(bool show);
  bool showHorzScroll(bool show);
  void setHorzRange(::i32 imin, ::i32 imax, ::i32 istep);
  void setVertRange(::i32 imin, ::i32 imax, ::i32 istep);
  void setVertPos(::i32 iPos);
  void setHorzPos(::i32 iPos);
  void moveUpVert(::i32 iPercent = 0);
  void moveDownVert(::i32 iPercent = 0);
  void moveLeftHorz(::i32 iPercent = 0);
  void moveRightHorz(::i32 inPercent = 0);
  ::i32 getVertPos();
  ::i32 getHorzPos();
  ::i32 getVerticalSize();
  ::i32 getHorizontalSize();

  static const ::i32 SCROLL_STEP = 5;
protected:
  void enableVirtualScroll();
  void disableVirtualScroll();
  bool _showVertScroll(bool show);
  bool _showHorzScroll(bool show);

  ::operating_system::window m_operatingsystemwindow;
  ::i32 m_vPos, m_hPos;
  ::i32 m_vMin, m_vMax;
  ::i32 m_hMin, m_hMax;
  ::i32 m_vStep;
  ::i32 m_hStep;
  bool m_isVirtualScroll;
  bool m_isVert;
  bool m_isHorz;
  bool m_isVVert;
  bool m_isVHorz;
};



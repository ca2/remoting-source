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
#include "framework.h"
#include "ToolBar.h"
// #include aaa_<commctrl.h>

HINSTANCE remoting_impact_hinstance();


namespace remoting
{
   ToolBar::ToolBar()
   {
      INITCOMMONCONTROLSEX initCtrlEx;

      initCtrlEx.dwSize = sizeof(INITCOMMONCONTROLSEX);
      initCtrlEx.dwICC  = ICC_BAR_CLASSES;
      InitCommonControlsEx(&initCtrlEx);

      m_hWndToolbar = 0;
      m_initialStr = -1;
   }

   ToolBar::~ToolBar()
   {
      if (m_hWndToolbar) {
         DestroyWindow(m_hWndToolbar);
      }
   }

   bool ToolBar::create(::i32 _tbID, HWND _parentHwnd, DWORD dwStyle)
   {
      dwStyle |= WS_CHILD;

      _ASSERT(m_hWndToolbar == 0);
      // Create the ToolBar window
      m_hWndToolbar = CreateWindowEx(0, TOOLBARCLASSNAME, 0, dwStyle,
                                     0, 0, 0, 0,
                                     _parentHwnd,
                                     reinterpret_cast<HMENU>((::iptr) _tbID),
                                     remoting_impact_hinstance(),
                                     0);
      if (m_hWndToolbar) {
         // It's required for backward compatibility
         SendMessage(m_hWndToolbar,
                     TB_BUTTONSTRUCTSIZE,
                     static_cast<::wparam>(sizeof(TBBUTTON)),
                     0);
      }
      return !!m_hWndToolbar;
   };

   void ToolBar::setViewAutoButtons(::i32 iButton, ::i32 style)
   {
      m_autoButtons[iButton] = style;
   }

   void ToolBar::loadToolBarfromRes(DWORD id)
   {
      BITMAP bmp;

      HBITMAP hbmp = LoadBitmap(remoting_impact_hinstance(),
                                MAKEINTRESOURCE(id));
      GetObject(hbmp, sizeof(BITMAP), &bmp);
      m_width = bmp.bmWidth;
      m_height = bmp.bmHeight;
      m_numberTB = m_width / m_height;
      m_id = id;
      DeleteObject(hbmp);
   }

   void ToolBar::setButtonsRange(DWORD id)
   {
      m_initialStr = id;
   }

   void ToolBar::attachToolBar(const ::operating_system::window & operatingsystemwindow)
   {
      ::array_base<TBBUTTON> tbuttons;

      for (::i32 i=0; i < m_numberTB; i++) {
         TBBUTTON tbutton;

         ZeroMemory(&tbutton, sizeof(tbutton));
         if (m_autoButtons.find(i) != m_autoButtons.end()) {
            // TODO: paste here all your variants of possible
            // toolbar buttons
            switch(m_autoButtons[i]) {
               case TB_Style_sep:
                  tbutton.fsStyle = TBSTYLE_SEP;
                  tbuttons.add(tbutton);
                  break;
               case TB_Style_gap:
                  tbutton.iBitmap = I_IMAGENONE;
                  tbuttons.add(tbutton);
                  break;
            }
         }
         tbutton.iBitmap = i;
         tbutton.idCommand = m_initialStr == 0 ? 0 : m_initialStr + i;
         tbutton.fsState   = TBSTATE_ENABLED;
         tbutton.fsStyle   = TBSTYLE_BUTTON;
         tbuttons.add(tbutton);
      }
      m_autoButtons.clear();

      m_hWndToolbar = CreateToolbarEx(hwnd,
         WS_VISIBLE | WS_CHILD | TBSTYLE_TOOLTIPS | WS_CLIPSIBLINGS | TBSTYLE_FLAT | WS_BORDER,
         m_id,
         static_cast<::i32>(tbuttons.size()),
         remoting_impact_hinstance(),
         m_id,
         tbuttons.data(),
         static_cast<::i32>(tbuttons.size()),
         0, 0, 0, 0,
         sizeof(TBBUTTON));
      SendMessage(m_hWndToolbar, TB_SETINDENT, 4, 0);
   }

   bool ToolBar::enableButton(::i32 idButton, bool enable)
   {
      LRESULT result = SendMessage(m_hWndToolbar, TB_ENABLEBUTTON,
                                   idButton, MAKELONG(enable, 0));
      return !!result;
   }

   bool ToolBar::pressButton(::i32 idButton, bool press)
   {
      LRESULT result = SendMessage(m_hWndToolbar, TB_PRESSBUTTON,
                                   idButton, MAKELONG(press, 0));
      return !!result;
   }

   bool ToolBar::getButtonRect(::i32 nIndex, LPRECT buttonRect)
   {
      LRESULT result = SendMessage(m_hWndToolbar, TB_GETITEMRECT,
                                   nIndex, (::lparam)buttonRect);
      return !!result;
   }

   bool ToolBar::setButtonsSize(const ::i32_size & size)
   {
      LRESULT result = SendMessage(m_hWndToolbar, TB_SETBUTTONSIZE,
                                   0, MAKELONG(width, height));
      if (result) {
         SendMessage(m_hWndToolbar, TB_AUTOSIZE, 0, 0);
         return true;
      }
      return false;
   }

   void ToolBar::autoSize()
   {
      LRESULT style = SendMessage(m_hWndToolbar, TB_GETSTYLE,  0, 0);
      if (style & CCS_NORESIZE) {
         RECT r, btnRect;
         GetClientRect(GetParent(m_hWndToolbar), &r);
         getButtonRect(0, &btnRect);
         ::i32 height = getButtonsHeight() + btnRect.top * 2 + 2;
         SetWindowPos(m_hWndToolbar, HWND_TOP, 0, 0, r.right - r.left, height,
                      SWP_NOMOVE);
      } else {
         SendMessage(m_hWndToolbar, TB_AUTOSIZE, 0, 0);
      }
   }

   ::i32 ToolBar::getButtonsHeight()
   {
      return HIWORD(SendMessage(m_hWndToolbar, TB_GETBUTTONSIZE, 0, 0));
   }

   ::i32 ToolBar::getButtonsWidth()
   {
      return LOWORD(SendMessage(m_hWndToolbar, TB_GETBUTTONSIZE, 0, 0));
   }

   ::i32 ToolBar::height()
   {
      RECT r;
      GetWindowRect(m_hWndToolbar, &r);
      return r.bottom - r.top;
   }

   ::i32 ToolBar::getTotalWidth()
   {
      SIZE size;
      SendMessage(m_hWndToolbar, TB_GETMAXSIZE, 0, reinterpret_cast<::lparam>(&size));
      return size.cx;
   }

   void ToolBar::show()
   {
      ShowWindow(m_hWndToolbar, SW_SHOW);
   }

   void ToolBar::hide()
   {
      ShowWindow(m_hWndToolbar, SW_HIDE);
   }

   bool ToolBar::isVisible()
   {
      LRESULT style = GetWindowLong(m_hWndToolbar, GWL_STYLE);
      return !!(style & WS_VISIBLE);
   }

   bool ToolBar::checkButton(::i32 idButton, bool check)
   {
      LRESULT result = SendMessage(m_hWndToolbar, TB_CHECKBUTTON,
              idButton, MAKELONG(check, 0));
      return !!result;
   }

   LRESULT ToolBar::getState(::i32 idButton)
   {
      LRESULT result = SendMessage(m_hWndToolbar, TB_GETSTATE,
                       idButton, 0);
      return result;
   }

   LRESULT ToolBar::addBitmap(::i32 nButtons, ::u32 bitmapID)
   {
      TBADDBITMAP resBitmap;

      resBitmap.hInst = remoting_impact_hinstance();
      resBitmap.nID = bitmapID;
      return SendMessage(m_hWndToolbar, TB_ADDBITMAP, nButtons, reinterpret_cast<::lparam>(&resBitmap));
   }

   LRESULT ToolBar::addSystemBitmap(::u32 stdBitmapID)
   {
      TBADDBITMAP resBitmap;

      resBitmap.hInst = HINST_COMMCTRL;
      resBitmap.nID = stdBitmapID;
      return SendMessage(m_hWndToolbar, TB_ADDBITMAP, 0, (::lparam)&resBitmap);
   }

   bool ToolBar::addButton(::i32 iBitmap, ::i32 idCommand, ::u8 state, ::u8 style, ::u32 dwData, ::i32 iString)
   {
      TBBUTTON tbb;

      tbb.iBitmap = iBitmap;
      tbb.idCommand = idCommand;
      tbb.fsState = state;
      tbb.fsStyle = style;
      tbb.dwData = dwData;
      tbb.iString = iString;

      LRESULT result = SendMessage(m_hWndToolbar, TB_ADDBUTTONS, 1, reinterpret_cast<::lparam>(&tbb));
      if (result) {
         SendMessage(m_hWndToolbar, TB_AUTOSIZE, 0, 0);
      }
      return !!result;
   }

   bool ToolBar::addNButton(::i32 nButtons, LPTBBUTTON tbb)
   {
      LRESULT result = SendMessage(m_hWndToolbar, TB_ADDBUTTONS, nButtons, reinterpret_cast<::lparam>(tbb));
      if (result) {
         SendMessage(m_hWndToolbar, TB_AUTOSIZE, 0, 0);
      }
      return !!result;
   }
}
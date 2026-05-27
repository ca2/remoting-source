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
// #include aaa_<commctrl.h>


namespace remoting
{
   class CLASS_DECL_REMOTING ToolBar
   {
   public:
      ToolBar();
      virtual ~ToolBar();

      static const ::i32 TB_Style_sep = 0;
      static const ::i32 TB_Style_gap = 1;

      /////////////////////////////////////////////////////////
      // Auto mode procedures
      /////////////////////////////////////////////////////////

      // setViewAutoButtons()
      // It used only for auto buttons creation from
      // bitmap and making gaps or separators.
      void setViewAutoButtons(::i32 iButton, ::i32 style);

      // loadToolBarfromRes()
      // This procedure will load a toolbar image from resource
      // id is a number of bitmap. It means that buttons are
      // square(for example 16x16).
      void loadToolBarfromRes(DWORD id);

      // setButtonsRange()
      // If we want to catch the scopedstrMessage from toolbar that some buttons
      // are pressed then we must set a range for scopedstrMessage, we pass only
      // first item, and next is id+1 and so on.
      void setButtonsRange(DWORD id);

      // attachToolBar()
      // This one will create and attach toolbar window to
      // which handle is passed in hwnd. Only for toolbar from bitmap.
      void attachToolBar(const ::operating_system::window & operatingsystemwindow);

      /////////////////////////////////////////////////////////
      // Manual mode procedures
      /////////////////////////////////////////////////////////

      // create() creates a windows toolbar. dwStyle is a combination of
      // the toolbar control and button styles. It returns true if successful,
      // or false otherwise.
      bool create(::i32 tbID, HWND parentHwnd,
           DWORD dwStyle = WS_CHILD | WS_VISIBLE | TBSTYLE_FLAT);

      // addBitmap() adds one or more images from resources to
      // the ::list_base of button images available for a toolbar.
      // Returns the index of the first new image if successful,
      // or -1 otherwise.
      LRESULT addBitmap(::i32 nButtons, ::u32 bitmapID);

      // addSystemBitmap() adds the system-defined button bitmaps to the ::list_base
      // of the toolbar button specifying by stdBitmapID. Returns the index of
      // the first new image if successful, or -1 otherwise.
      LRESULT addSystemBitmap(::u32 stdBitmapID);

      // addNButton() adds nButtons buttons to a toolbar.
      bool addNButton(::i32 nButtons, LPTBBUTTON tbb);

      // addButton() adds one button.
      bool addButton(::i32 iBitmap, ::i32 idCommand, ::u8 state=TBSTATE_ENABLED,
                     ::u8 style=TBSTYLE_BUTTON,  ::u32 dwData=0, ::i32 iString=0);

      // checkButton() checks or unchecks a given button in a toolbar control.
      bool checkButton(::i32 idButton, bool check);

      // enableButton() enables or disables the specified button
      // in the toolbar.
      bool enableButton(::i32 idButton, bool enable);

      // pressButton() presses or releases the specified button in the toolbar.
      bool pressButton(::i32 idButton, bool press);

      // getButtonRect() gets the bounding rectangle of a button in a toolbar.
      bool getButtonRect(::i32 nIndex, LPRECT buttonRect);

      // setButtonSize() sets the size of the buttons to be added to a toolbar.
      // Button size must be largen the button bitmap.
      bool setButtonsSize(const ::i32_size & size);

      // autoSize() resizes the toolbar window.
      void autoSize();

      // getButtonsHeight() retrieves the height of the toolbar buttons.
      ::i32 getButtonsHeight();

      // getButtonsWidth() retrieves the width of the toolbar buttons.
      ::i32 getButtonsWidth();

      // isVisible() check the toolbar window on visible.
      bool isVisible();

      // hide() hides the toolbar window.
      void hide();

      // show() displays the toolbar window.
      void show();

      // getTotalWidth() returns the total size of all buttons and
      // separators in the toolbar.
      ::i32 getTotalWidth();

      // getHeight() returns the toolbar window height.
      ::i32 height();

      // getState() gets button state
      LRESULT getState(::i32 idButton);

   private:
      ::i32 m_initialStr;
      ::i32 m_numberTB;
      DWORD m_id;
      ::i32 m_width, m_height;
      HWND m_hWndToolbar;

      ::map<::i32, ::i32> m_autoButtons;
   };
}
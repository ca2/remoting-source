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
#include "subsystem/_common_header.h"
#include "BaseWindow.h"
#include "acme/prototype/geometry2d/_function.h"

HINSTANCE remoting_impact_hinstance();

BaseWindow::BaseWindow()
: //m_hwnd(0),
  m_hicon(0),
  m_bWndCreated(false)
{
}

BaseWindow::~BaseWindow()
{
  if (m_bWndCreated && m_hwnd) {
    DestroyWindow(m_hwnd);
  }
  if (m_hicon) {
    DeleteObject(m_hicon);
  }
}

void BaseWindow::setClass(const ::scoped_string & className)
{
  m_className = className;
}

bool BaseWindow::createWindow(const ::scoped_string & windowName, DWORD style, HWND hWndParent,
                              ::i32 xPos, ::i32 yPos, const ::i32_size & size)
{
  if (m_hwnd) {
    return false;
  }
  m_windowName = windowName;
  m_hwnd = CreateWindow(::wstring(m_className),
                        ::wstring(m_windowName),
                        style, 
                        xPos, yPos, 
                        width, height, 
                        hWndParent, 
                        0, 
                        //GetModuleHandle(0),
                        remoting_impact_hinstance(),
                        reinterpret_cast<LPVOID>(this));
  m_bWndCreated = (m_hwnd == 0 ? false : true);
  if (m_bWndCreated) {
      SetWindowLongPtr(m_hwnd, 
                       GWLP_USERDATA, 
                       reinterpret_cast<LONG_PTR>(this));
  }
  return true;
}

void BaseWindow::loadIcon(DWORD id)
{
  if (m_hicon) {
    DeleteObject(m_hicon);
    m_hicon = 0;
  }
  if (IS_INTRESOURCE(id)) {
    m_hicon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(id));
    SetClassLongPtr(m_hwnd, GCLP_HICON, reinterpret_cast<LONG_PTR>(m_hicon));
  } else {
    SetClassLongPtr(m_hwnd, GCLP_HICON, static_cast<LONG_PTR>(id));
  }
}

void BaseWindow::enableWindow(bool bEnable)
{
  _ASSERT(m_hwnd != 0);
  EnableWindow(m_hwnd, bEnable);
}

bool BaseWindow::destroyWindow()
{
  if (m_hwnd) {
    DestroyWindow(m_hwnd);
    return true;
  }
  return false;
}

void BaseWindow::show()
{
  _ASSERT(m_hwnd != 0);
  ShowWindow(m_hwnd, SW_SHOW);
}

void BaseWindow::hide()
{
  _ASSERT(m_hwnd != 0);
  ShowWindow(m_hwnd, SW_HIDE);
}

bool BaseWindow::setSize(const ::i32_size & size)
{
  _ASSERT(m_hwnd != 0);
  return !!SetWindowPos(m_hwnd, 0, 0, 0, width, height, 
                        SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
}

bool BaseWindow::setPosition(::i32 xPos, ::i32 yPos)
{
  _ASSERT(m_hwnd != 0);
  return !!SetWindowPos(m_hwnd, 0, xPos, yPos, 0, 0, 
                        SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
}

void BaseWindow::setParent(const ::operating_system::window & operatingsystemwindow)
{
  _ASSERT(m_hwnd != 0);
  SetParent(m_hwnd, hwnd);
}

void BaseWindow::setClassStyle(DWORD style)
{
  _ASSERT(m_hwnd != 0);
  SetClassLong(m_hwnd, GCL_STYLE, style);
}

void BaseWindow::setClassCursor(HCURSOR hcursor)
{
  _ASSERT(m_hwnd != 0);
  SetClassLongPtr(m_hwnd, GCLP_HCURSOR, reinterpret_cast<LONG_PTR>(hcursor));
}

void BaseWindow::setClassBackground(HBRUSH hbrush)
{
  _ASSERT(m_hwnd != 0);
  SetClassLongPtr(m_hwnd, GCLP_HBRBACKGROUND, reinterpret_cast<LONG_PTR>(hbrush));
}

void BaseWindow::setClassMenu(LONG menu)
{
  _ASSERT(m_hwnd != 0);
  SetClassLongPtr(m_hwnd, GCLP_MENUNAME, menu);
}

LONG BaseWindow::get_style()
{
  _ASSERT(m_hwnd != 0);
  return GetWindowLong(m_hwnd, GWL_STYLE);
}

void BaseWindow::set_style(DWORD style)
{
  _ASSERT(m_hwnd != 0);
  SetWindowLong(m_hwnd, GWL_STYLE, style);
}

LONG BaseWindow::get_ex_style()
{
  _ASSERT(m_hwnd != 0);
  return GetWindowLong(m_hwnd, GWL_EXSTYLE);
}

void BaseWindow::set_ex_style(DWORD exstyle)
{
  _ASSERT(m_hwnd != 0);
  SetWindowLong(m_hwnd, GWL_EXSTYLE, exstyle);
}

void BaseWindow::updateWindow()
{
  _ASSERT(m_hwnd != 0);
  UpdateWindow(m_hwnd);
}

void BaseWindow::setTimer(UINT_PTR ident, ::u32 time)
{
  _ASSERT(m_hwnd != 0);
  SetTimer(m_hwnd, ident, time, 0);
}

void BaseWindow::killTimer(UINT_PTR ident)
{
  _ASSERT(m_hwnd != 0);
  KillTimer(m_hwnd, ident);
}

bool BaseWindow::onCommand(::wparam wParam, ::lparam lParam)
{
  return false;
}

bool BaseWindow::onNotify(::i32 idCtrl, LPNMHDR pnmh)
{
  return false;
}

bool BaseWindow::onSysCommand(::wparam wParam, ::lparam lParam)
{
  return false;
}

bool BaseWindow::onMessage(::u32 scopedstrMessage, ::wparam wParam, ::lparam lParam)
{
  return false;
}

bool BaseWindow::wndProc(::u32 scopedstrMessage, ::wparam wParam, ::lparam lParam)
{
    if (scopedstrMessage == WM_LBUTTONDOWN)
    {

        OutputDebugString(L"WM_LBUTTONDOWN");

    }
  switch (scopedstrMessage) {
    case WM_COMMAND:
      return onCommand(wParam, lParam);
    case WM_NOTIFY:
      return onNotify((::i32)wParam, (LPNMHDR)lParam);
    case WM_SYSCOMMAND:
      return onSysCommand(wParam, lParam);
    case WM_LBUTTONDOWN:
    case WM_LBUTTONUP:
    case WM_MBUTTONDOWN:
    case WM_MBUTTONUP:
    case WM_RBUTTONDOWN:
    case WM_RBUTTONUP:
    case WM_MOUSEWHEEL:
    case WM_MOUSEMOVE:
    {


      ::u8 mouseButtons = 0;

      mouseButtons |= LOWORD(wParam) & MK_RBUTTON ? MOUSE_RDOWN : 0;
      mouseButtons |= LOWORD(wParam) & MK_MBUTTON ? MOUSE_MDOWN : 0;
      mouseButtons |= LOWORD(wParam) & MK_LBUTTON ? MOUSE_LDOWN : 0;

      // Translate pointPosition from ::lparam to POINT.
      POINTS points = MAKEPOINTS(lParam);
      POINT point;
      point.x = points.x;
      point.y = points.y;

      ::u16 wheelSpeed = 0; 
      if (scopedstrMessage == WM_MOUSEWHEEL) {
        // Get speed wheel and set mouse button.
        ::i16 wheelSignedSpeed = static_cast<::i16>(HIWORD(wParam));
        if (wheelSignedSpeed < 0) {
          mouseButtons |= MOUSE_WDOWN;
          wheelSpeed = - wheelSignedSpeed * 24 / WHEEL_DELTA;
        } else {
          mouseButtons |= MOUSE_WUP;
          wheelSpeed = wheelSignedSpeed * 24 / WHEEL_DELTA;
        }

        // In some cases wheelSignedSpeed can be smaller than the WHEEL_DELTA,
        // then wheelSpeed set to 1, but not 0.
        if (wheelSpeed == 0) {
          wheelSpeed = 1;
        }

        // If windows-scopedstrMessage is WHEEL, then need to translate screen coordinate to client.
        if (!ScreenToClient(getHWnd(), &point)) {
          point.x = -1;
          point.y = -1;
        }

      }

      if (onMouseEx(scopedstrMessage,mouseButtons, wheelSpeed, point))
        {

          return true;

        }
          

      // Notify window about mouse-event.
      return onMouse(mouseButtons, static_cast<::u16>(wheelSpeed), point);
    }
  }
  return onMessage(scopedstrMessage, wParam, lParam);
}

void BaseWindow::setHWnd(const ::operating_system::window & operatingsystemwindow)
{
  m_hwnd = hwnd;
}

HWND BaseWindow::getHWnd() const
{
  return m_hwnd;
}

void BaseWindow::setWindowText(const ::scoped_string & scopedstrText)
{
  _ASSERT(m_hwnd != 0);
  SetWindowText(m_hwnd, ::wstring(scopedstrText).c_str());
}

void BaseWindow::redraw(const RECT & rectArea)
{
  _ASSERT(m_hwnd != 0);

  if (!::IsWindowVisible(m_hwnd) || IsIconic(m_hwnd) || ::IsIconic(::GetParent(m_hwnd)))
  {

      return;
  }

  if (::is_empty(rectArea)) {
     InvalidateRect(m_hwnd, NULL, true);
  } else {
     InvalidateRect(m_hwnd, &rectArea, false);
  }
}

bool BaseWindow::onMouse(::u8 msg, ::u16 wspeed, POINT pt)
{
  return false;
}

bool BaseWindow::onMouseEx(::u32 message, ::i32 iButtonMask, ::u16 wspeed, POINT pt)
{
    return false;

}

void BaseWindow::setForegroundWindow()
{
  _ASSERT(m_hwnd != 0);

  SetForegroundWindow(m_hwnd);
}

void BaseWindow::postMessage(::u32 Msg, ::wparam wParam, ::lparam lParam)
{
  _ASSERT(m_hwnd != 0);

  PostMessage(m_hwnd, Msg, wParam, lParam);
}

void BaseWindow::getClientRect(RECT *rc)
{
  _ASSERT(m_hwnd != 0 && rc);

  GetClientRect(m_hwnd, rc);
}

void BaseWindow::getBorderSize(::i32 *width, ::i32 *height)
{
  _ASSERT(m_hwnd != 0);

  *width = 2 * GetSystemMetrics(SM_CXSIZEFRAME);
  *height = GetSystemMetrics(SM_CYSIZE) +
            2 * GetSystemMetrics(SM_CYSIZEFRAME);
}

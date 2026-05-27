// Copyright (C) 2012 GlavSoft LLC.
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
#include "subsystem/platform/Exception.h"

// The header including of this cpp file must be at last place to avoid build conflicts.
#include "../WinAutoMapDxgiSurface.h"

namespace remoting
{


   WinAutoMapDxgiSurface::WinAutoMapDxgiSurface(WinDxgiSurface *surface, ::u32 mapFlags) : m_surface(surface)
   {
      HRESULT hr = m_surface->getSurface()->Map(&m_mappedRect, mapFlags);
      if (FAILED(hr))
      {
         ::string errMess;
         errMess.formatf("Can't IDXGISurface->Map, error code = %l", (long)hr);
         throw ::subsystem::Exception(errMess);
      }
   }

   WinAutoMapDxgiSurface::~WinAutoMapDxgiSurface() { m_surface->getSurface()->Unmap(); }

   size_t WinAutoMapDxgiSurface::getStride() const
   {
      if (m_mappedRect.Pitch < 0)
      {
         throw ::subsystem::Exception("DXGI_MAPPED_RECT::Pitch is negative");
      }
      return (size_t)m_mappedRect.Pitch;
   }

   char_pointer WinAutoMapDxgiSurface::getBuffer() const { return (char_pointer )m_mappedRect.pBits; }


} // namespace remoting

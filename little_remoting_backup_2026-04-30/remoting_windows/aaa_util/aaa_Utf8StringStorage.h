//// Copyright (C) 2010,2011,2012 GlavSoft LLC.
//// All rights reserved.
////
////-------------------------------------------------------------------------
//// This file is part of the T i g h t V N C software.  Please visit our Web site:
////
////                       http://www.t i g h t v n c.com/
////
//// This program is free software; you can redistribute it and/or modify
//// it under the terms of the GNU General Public License as published by
//// the Free Software Foundation; either version 2 of the License, or
//// (at your option) any later version.
////
//// This program is distributed in the hope that it will be useful,
//// but WITHOUT ANY WARRANTY; without even the implied warranty of
//// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//// GNU General Public License for more details.
////
//// You should have received a copy of the GNU General Public License along
//// with this program; if not, w_rite to the Free Software Foundation, Inc.,
//// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
////-------------------------------------------------------------------------
////
//#pragma once
//
//class ::string;
//
////#include aaa_<vector>
//
//// Note: The ::string class contains utf8 symbols "as is". The class
//// do not adds termination symbol(s) and do not remove it when
//// it already presented.
//class ::string
//{
//private:
//
//   ::array_base<::i8> m_buffer;
//
//public:
//  ::string();
//  ::string(const ::array_base<::i8> *utf8Buffer);
//  ::string(const ::scoped_string & string);
//  ::string(const ::string &string);
//  ~::string();
//
//  // Sets internal buffer by an external utf8 string.
//  void= const ::array_base<::i8> *utf8Buffer;
//
//  // Returns pointer to the string.
//  const_char_pointer getString() const;
//
//  // Returns size of string in bytes, including terminating null character.
//  memsize getSize() const;
//  // Returns length of string (in characters, not including terminating null character).
//  memsize length() const;
//  void fromStringStorage(const ::scoped_string & src);
//  void toStringStorage(::string & dst);
//
//};
//
//
//
//

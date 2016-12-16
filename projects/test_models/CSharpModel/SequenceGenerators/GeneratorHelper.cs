// -*- mode: csharp; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
//
// Copyright (C) 2012-2015 Marco Craveiro <marco.craveiro@gmail.com>
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
// MA 02110-1301, USA.
//
using System;

namespace Dogen.TestModels.CSharpModel
{
    /// <summary>
    /// Provides helper methods for the sequence generators.
    /// </summary>
    static class GeneratorHelper
    {
        public static object CreateObject(uint position)
        {
            return "this is an object: " + Convert.ToString(position);
        }

        public static string CreateString(uint position)
        {
            return "this is a string: " + Convert.ToString(position);
        }

        public static byte CreateByte(uint position)
        {
            return Convert.ToByte(position);
        }

        public static sbyte CreateShortByte(uint position)
        {
            return Convert.ToSByte(position);
        }

        public static int CreateInt(uint position)
        {
            return Convert.ToInt32(position);
        }

        public static uint CreateUInt(uint position)
        {
            return position;
        }

        public static short CreateShort(uint position)
        {
            return Convert.ToInt16(position);
        }

        public static ushort CreateUShort(uint position)
        {
            return Convert.ToUInt16(position);
        }

        public static long CreateLong(uint position)
        {
            return Convert.ToInt64(position);
        }

        public static ulong CreateULong(uint position)
        {
            return Convert.ToUInt64(position);
        }

        public static float CreateFloat(uint position)
        {
            return Convert.ToSingle(position);
        }

        public static double CreateDouble(uint position)
        {
            return Convert.ToDouble(position);
        }

        public static char CreateChar(uint position)
        {
            return Convert.ToChar(position);
        }

        public static bool CreateBool(uint position)
        {
            return position % 2 == 0;
        }

        public static decimal CreateDecimal(uint position)
        {
            return Convert.ToDecimal(position);
        }
    }
}


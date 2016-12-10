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
namespace Dogen.TestModels.CSharpModel
{
    /// <summary>
    /// This is a class made up of just built-in types.
    /// </summary>
    /// <remarks>
    /// This is a remark.
    /// </remarks>
    class AllBuiltins
    {
        public byte byte_property { get; set; }
        public sbyte short_byte_property { get; set; }
        public int int_property { get; set; }
        public uint uint_property { get; set; }
        public short short_property { get; set; }
        public ushort ushort_property { get; set; }
        public long long_property { get; set; }
        public ulong ulong_property { get; set; }
        public float float_property { get; set; }
        public double double_property { get; set; }
        public char char_property { get; set; }
        public bool bool_property { get; set; }
        public object object_property { get; set; }
        public string string_property { get; set; }
        public decimal decimal_property { get; set; }
    };
}

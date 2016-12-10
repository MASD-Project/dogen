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
        /// <summary>
        /// A comment at property level.
        /// </summary>
        public byte ByteProperty { get; set; }
        /// <summary>
        /// A comment at property level.
        /// </summary>
        /// <remarks>
        /// This is a remark.
        /// </remarks>
        public sbyte ShortByteProperty { get; set; }
        public int IntProperty { get; set; }
        public uint UIntProperty { get; set; }
        public short ShortProperty { get; set; }
        public ushort UShortProperty { get; set; }
        public long LongProperty { get; set; }
        public ulong ULongProperty { get; set; }
        public float FloatProperty { get; set; }
        public double DoubleProperty { get; set; }
        public char CharProperty { get; set; }
        public bool BoolProperty { get; set; }
        public object ObjectProperty { get; set; }
        public string StringProperty { get; set; }
        public decimal DecimalProperty { get; set; }
    };
}

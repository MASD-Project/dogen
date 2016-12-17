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
    /// Generates sequences of PrimitiveBuiltins.
    /// </summary>
    public static class PrimitiveBuiltinsDumper
    {
        static void Dump(DumpHelper helper, PrimitiveBuiltins value)
        {
            helper.IncrementDepth();
            if (helper.MaximumDepthExceeded())
                return;

            helper.AddStartObject();
            helper.AddType("Dogen.TestModels.CSharpModel.PrimitiveBuiltins", true/*withSeparator*/);
            helper.Add("ByteProperty", value.ByteProperty, true/*withSeparator*/);
            helper.Add("ShortByteProperty", value.ShortByteProperty, true/*withSeparator*/);
            helper.Add("IntProperty", value.IntProperty, true/*withSeparator*/);
            helper.Add("UIntProperty", value.UIntProperty, true/*withSeparator*/);
            helper.Add("ShortProperty", value.ShortProperty, true/*withSeparator*/);
            helper.Add("UShortProperty", value.UShortProperty, true/*withSeparator*/);
            helper.Add("LongProperty", value.LongProperty, true/*withSeparator*/);
            helper.Add("ULongProperty", value.ULongProperty, true/*withSeparator*/);
            helper.Add("FloatPropertyOne", value.FloatPropertyOne, true/*withSeparator*/);
            helper.Add("FloatPropertyTwo", value.FloatPropertyTwo, true/*withSeparator*/);
            helper.Add("DoublePropertyOne", value.DoublePropertyOne, true/*withSeparator*/);
            helper.Add("DoublePropertyTwo", value.DoublePropertyTwo, true/*withSeparator*/);
            helper.Add("CharProperty", value.CharProperty, true/*withSeparator*/);
            helper.Add("BoolProperty", value.BoolProperty, true/*withSeparator*/);
            helper.Add("DecimalProperty", value.DecimalProperty);
            helper.AddEndObject();

            helper.DecrementDepth();
        }

        public static string Dump(PrimitiveBuiltins value)
        {
            var helper = new DumpHelper();
            Dump(helper, value);
            return helper.Dump();
        }
    }
}

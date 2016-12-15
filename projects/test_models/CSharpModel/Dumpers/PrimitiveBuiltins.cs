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
using System.Text;

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
			helper.AddType("Dogen.TestModels.CSharpModel.PrimitiveBuiltinsDumper", withSeparator:true);
			helper.Add("ByteProperty", value.ByteProperty, withSeparator:true);
			helper.Add("ShortByteProperty", value.ShortByteProperty, withSeparator:true);
			helper.Add("IntProperty", value.IntProperty, withSeparator:true);
			helper.Add("UIntProperty", value.UIntProperty, withSeparator:true);
			helper.Add("ShortProperty", value.ShortProperty, withSeparator:true);
			helper.Add("UShortProperty", value.UShortProperty, withSeparator:true);
			helper.Add("LongProperty", value.LongProperty, withSeparator:true);
			helper.Add("ULongProperty", value.ULongProperty, withSeparator:true);
			helper.Add("FloatPropertyOne", value.FloatPropertyOne, withSeparator:true);
			helper.Add("FloatPropertyTwo", value.FloatPropertyTwo, withSeparator:true);
			helper.Add("DoublePropertyOne", value.DoublePropertyOne, withSeparator:true);
			helper.Add("DoublePropertyTwo", value.DoublePropertyTwo, withSeparator:true);
			helper.Add("CharProperty", value.CharProperty, withSeparator:true);
			helper.Add("BoolProperty", value.BoolProperty, withSeparator:true);
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

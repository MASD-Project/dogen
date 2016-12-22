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
    /// Generates sequences of PrimitiveBuiltins.
    /// </summary>
    public static class PrimitiveBuiltinsDumper
    {
        static internal void Dump(AssistantDumper assistant, PrimitiveBuiltins value, bool withSeparator = false)
        {
            assistant.IncrementDepth();
            if (assistant.MaximumDepthExceeded())
                return;

            assistant.AddStartObject();
            assistant.AddType("Dogen.TestModels.CSharpModel.PrimitiveBuiltins", true/*withSeparator*/);
            if (value == null)
            {
                assistant.Add("data", "<null>");
                assistant.AddEndObject();
                return;
            }

            assistant.AddKey("data");
            assistant.AddPairSeparator();
            assistant.AddStartObject();
            assistant.Add("ByteProperty", value.ByteProperty, true/*withSeparator*/);
            assistant.Add("ShortByteProperty", value.ShortByteProperty, true/*withSeparator*/);
            assistant.Add("IntProperty", value.IntProperty, true/*withSeparator*/);
            assistant.Add("UIntProperty", value.UIntProperty, true/*withSeparator*/);
            assistant.Add("ShortProperty", value.ShortProperty, true/*withSeparator*/);
            assistant.Add("UShortProperty", value.UShortProperty, true/*withSeparator*/);
            assistant.Add("LongProperty", value.LongProperty, true/*withSeparator*/);
            assistant.Add("ULongProperty", value.ULongProperty, true/*withSeparator*/);
            assistant.Add("FloatPropertyOne", value.FloatPropertyOne, true/*withSeparator*/);
            assistant.Add("FloatPropertyTwo", value.FloatPropertyTwo, true/*withSeparator*/);
            assistant.Add("DoublePropertyOne", value.DoublePropertyOne, true/*withSeparator*/);
            assistant.Add("DoublePropertyTwo", value.DoublePropertyTwo, true/*withSeparator*/);
            assistant.Add("CharProperty", value.CharProperty, true/*withSeparator*/);
            assistant.Add("BoolProperty", value.BoolProperty, true/*withSeparator*/);
            assistant.Add("DecimalProperty", value.DecimalProperty);
            assistant.AddEndObject(); // data
            assistant.AddEndObject(); // main object
            assistant.HandleMemberSeparator(withSeparator);

            assistant.DecrementDepth();
        }

        public static string Dump(PrimitiveBuiltins value)
        {
            var assistant = new AssistantDumper();
            Dump(assistant, value);
            return assistant.ToString();
        }
    }
}

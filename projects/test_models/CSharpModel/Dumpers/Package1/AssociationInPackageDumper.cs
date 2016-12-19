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

namespace Dogen.TestModels.CSharpModel.Package1
{
    /// <summary>
    /// Generates sequences of AssociationInPackage.
    /// </summary>
    public static class AssociationInPackageDumper
    {
        static internal void Dump(AssistantDumper assistant, AssociationInPackage value, bool withSeparator = false)
        {
            assistant.IncrementDepth();
            if (assistant.MaximumDepthExceeded())
                return;

            assistant.AddStartObject();
            assistant.AddType("Dogen.TestModels.CSharpModel.Package1.AssociationInPackage", true/*withSeparator*/);
            if (value == null)
            {
                assistant.Add("data", "<null>");
                assistant.AddEndObject();
                return;
            }

            assistant.AddKey("data");
            assistant.AddPairSeparator();
            assistant.AddStartObject();
            assistant.AddKey("Prop0");
            assistant.AddPairSeparator();
            Dogen.TestModels.CSharpModel.PrimitiveBuiltinsDumper.Dump(assistant, value.Prop0, true/*withSeparator*/);
            assistant.AddKey("Prop1");
            assistant.AddPairSeparator();
            Dogen.TestModels.CSharpModel.ComplexBuiltinsDumper.Dump(assistant, value.Prop1, true/*withSeparator*/);
            assistant.AddKey("Prop2");
            assistant.AddPairSeparator();
            Dogen.TestModels.CSharpModel.Package1.Class1Dumper.Dump(assistant, value.Prop2);
            assistant.AddEndObject(); // data
            assistant.AddEndObject(); // main object
            assistant.HandleMemberSeparator(withSeparator);

            assistant.DecrementDepth();
        }

        public static string Dump(AssociationInPackage value)
        {
            var assistant = new AssistantDumper();
            Dump(assistant, value);
            return assistant.Dump();
        }
    }
}

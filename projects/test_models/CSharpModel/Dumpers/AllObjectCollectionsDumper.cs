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
    /// Generates sequences of AllObjectCollections.
    /// </summary>
    public static class AllObjectCollectionsDumper
    {
        static internal void Dump(AssistantDumper assistant, AllObjectCollections value, bool withSeparator = false)
        {
            assistant.IncrementDepth();
            if (assistant.MaximumDepthExceeded())
                return;

            assistant.AddStartObject();
            assistant.AddType("Dogen.TestModels.CSharpModel.AllObjectCollections", true/*withSeparator*/);
            if (value == null)
            {
                assistant.Add("data", "<null>");
                assistant.AddEndObject();
                return;
            }

            assistant.AddKey("data");
            assistant.AddPairSeparator();
            assistant.AddStartObject();
            assistant.Add("Prop0", value.Prop0, true/*withSeparator*/);
            assistant.Add("Prop1", value.Prop1, true/*withSeparator*/);
            assistant.Add("Prop2", value.Prop2, true/*withSeparator*/);
            assistant.Add("Prop3", value.Prop3, true/*withSeparator*/);
            assistant.Add("Prop4", value.Prop4, true/*withSeparator*/);
            assistant.Add("Prop5", value.Prop5, true/*withSeparator*/);
            assistant.Add("Prop6", value.Prop6, true/*withSeparator*/);
            assistant.Add("Prop7", value.Prop7);
            assistant.AddEndObject(); // data
            assistant.AddEndObject(); // main object
            assistant.HandleMemberSeparator(withSeparator);

            assistant.DecrementDepth();
        }

        public static string Dump(AllObjectCollections value)
        {
            var assistant = new AssistantDumper();
            Dump(assistant, value);
            return assistant.ToString();
        }
    }
}

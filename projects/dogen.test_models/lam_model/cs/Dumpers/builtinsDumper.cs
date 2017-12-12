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

namespace dogen.test_models.lam_model
{
    /// <summary>
    /// Generates sequences of builtins.
    /// </summary>
    public static class builtinsDumper
    {
        static internal void Dump(AssistantDumper assistant, builtins value, bool withSeparator = false)
        {
            assistant.IncrementDepth();
            if (assistant.MaximumDepthExceeded())
                return;

            assistant.AddStartObject();
            assistant.AddType("dogen.test_models.lam_model.builtins", true/*withSeparator*/);
            if (value == null)
            {
                assistant.Add("data", "<null>");
                assistant.AddEndObject();
                return;
            }

            assistant.AddKey("data");
            assistant.AddPairSeparator();
            assistant.AddStartObject();
            assistant.Add("prop_0", value.prop_0, true/*withSeparator*/);
            assistant.Add("prop_1", value.prop_1, true/*withSeparator*/);
            assistant.Add("prop_2", value.prop_2, true/*withSeparator*/);
            assistant.Add("prop_3", value.prop_3, true/*withSeparator*/);
            assistant.Add("prop_4", value.prop_4, true/*withSeparator*/);
            assistant.Add("prop_5", value.prop_5, true/*withSeparator*/);
            assistant.Add("prop_6", value.prop_6, true/*withSeparator*/);
            assistant.Add("prop_7", value.prop_7, true/*withSeparator*/);
            assistant.Add("prop_8", value.prop_8, true/*withSeparator*/);
            assistant.Add("prop_9", value.prop_9);
            assistant.AddEndObject(); // data
            assistant.AddEndObject(); // main object
            assistant.HandleMemberSeparator(withSeparator);

            assistant.DecrementDepth();
        }

        public static string Dump(builtins value)
        {
            var assistant = new AssistantDumper();
            Dump(assistant, value);
            return assistant.ToString();
        }
    }
}

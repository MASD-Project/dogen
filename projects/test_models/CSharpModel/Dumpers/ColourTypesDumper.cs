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
    /// Generates sequences of ColourTypes.
    /// </summary>
    public static class ColourTypesDumper
    {
        static void Dump(AssistantDumper assistant, ColourTypes value)
        {
            assistant.IncrementDepth();
            if (assistant.MaximumDepthExceeded())
                return;

            assistant.AddStartObject();
            assistant.AddType("Dogen.TestModels.CSharpModel.ColourTypes", true/*withSeparator*/);
            string valueAsString = "Unsupported Value";
            switch (value)
            {
                case ColourTypes.Invalid:
                    valueAsString = "Invalid";
                    break;
                case ColourTypes.Red:
                    valueAsString = "Red";
                    break;
                case ColourTypes.Blue:
                    valueAsString = "Blue";
                    break;
                case ColourTypes.Green:
                    valueAsString = "Green";
                    break;
                case ColourTypes.Gray:
                    valueAsString = "Gray";
                    break;
            }

            assistant.Add("value", valueAsString);
            assistant.AddEndObject();

            assistant.DecrementDepth();
        }

        public static string Dump(ColourTypes value)
        {
            var assistant = new AssistantDumper();
            Dump(assistant, value);
            return assistant.Dump();
        }
    }
}

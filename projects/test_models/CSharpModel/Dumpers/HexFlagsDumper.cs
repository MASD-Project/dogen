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
    /// Generates sequences of HexFlags.
    /// </summary>
    public static class HexFlagsDumper
    {
        static internal void Dump(AssistantDumper assistant, HexFlags value, bool withSeparator = false)
        {
            assistant.IncrementDepth();
            if (assistant.MaximumDepthExceeded())
                return;

            assistant.AddStartObject();
            assistant.AddType("Dogen.TestModels.CSharpModel.HexFlags", true/*withSeparator*/);
            string valueAsString = "Unsupported Value";
            switch (value)
            {
                case HexFlags.None:
                    valueAsString = "None";
                    break;
                case HexFlags.Top:
                    valueAsString = "Top";
                    break;
                case HexFlags.Bottom:
                    valueAsString = "Bottom";
                    break;
                case HexFlags.Left:
                    valueAsString = "Left";
                    break;
                case HexFlags.Right:
                    valueAsString = "Right";
                    break;
            }

            assistant.Add("value", valueAsString);
            assistant.AddEndObject();

            assistant.DecrementDepth();
        }

        public static string Dump(HexFlags value)
        {
            var assistant = new AssistantDumper();
            Dump(assistant, value);
            return assistant.ToString();
        }
    }
}

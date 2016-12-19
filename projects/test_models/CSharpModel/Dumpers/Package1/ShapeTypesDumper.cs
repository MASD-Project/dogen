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
namespace Dogen.TestModels.CSharpModel.Package1
{
    /// <summary>
    /// Generates sequences of ShapeTypes.
    /// </summary>
    public static class ShapeTypesDumper
    {
        static void Dump(AssistantDumper assistant, ShapeTypes value)
        {
            assistant.IncrementDepth();
            if (assistant.MaximumDepthExceeded())
                return;

            assistant.AddStartObject();
            assistant.AddType("Dogen.TestModels.CSharpModel.Package1.ShapeTypes", true/*withSeparator*/);
            string valueAsString = "Unsupported Value";
            switch (value)
            {
                case ShapeTypes.invalid:
                    valueAsString = "invalid";
                    break;
                case ShapeTypes.Triangle:
                    valueAsString = "Triangle";
                    break;
                case ShapeTypes.Square:
                    valueAsString = "Square";
                    break;
                case ShapeTypes.Rectangle:
                    valueAsString = "Rectangle";
                    break;
                case ShapeTypes.Cube:
                    valueAsString = "Cube";
                    break;
            }

            assistant.Add("value", valueAsString);
            assistant.AddEndObject();

            assistant.DecrementDepth();
        }

        public static string Dump(ShapeTypes value)
        {
            var assistant = new AssistantDumper();
            Dump(assistant, value);
            return assistant.Dump();
        }
    }
}

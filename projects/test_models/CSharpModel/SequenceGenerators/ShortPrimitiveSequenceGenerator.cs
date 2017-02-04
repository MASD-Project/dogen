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
using System.Collections;
using System.Collections.Generic;

namespace Dogen.TestModels.CSharpModel
{
    /// <summary>
    /// Generates sequences of ShortPrimitive.
    /// </summary>
    public static class ShortPrimitiveSequenceGenerator
    {
        static internal void Populate(ShortPrimitive value, uint position)
        {
            value.Value = AssistantSequenceGenerator.CreateShort(position);
        }

        static internal ShortPrimitive Create(uint position)
        {
            var result = new ShortPrimitive();
            Populate(result, position);
            return result;
        }

        #region Enumerator
        private class ShortPrimitiveEnumerator : IEnumerator, IEnumerator<ShortPrimitive>, IDisposable
        {
            #region Properties
            private uint _position;
            private ShortPrimitive _current;
            #endregion

            private void PopulateCurrent()
            {
                _current = ShortPrimitiveSequenceGenerator.Create(_position);
            }

            #region IDisposable
            public void Dispose()
            {
            }
            #endregion

            #region IEnumerator implementation
            public bool MoveNext()
            {
                ++_position;
                PopulateCurrent();
                return true;
            }

            public void Reset()
            {
                _position = 0;
                PopulateCurrent();
            }

            public object Current {
                get
                {
                    return _current;
                }
            }

            ShortPrimitive IEnumerator<ShortPrimitive>.Current
            {
                get
                {
                    return _current;
                }
            }
            #endregion

            public ShortPrimitiveEnumerator()
            {
                PopulateCurrent();
            }
        }
        #endregion

        #region Enumerable
        private class ShortPrimitiveEnumerable : IEnumerable, IEnumerable<ShortPrimitive>
        {
            #region IEnumerable implementation
            public IEnumerator GetEnumerator()
            {
                return new ShortPrimitiveEnumerator();
            }

            IEnumerator<ShortPrimitive> IEnumerable<ShortPrimitive>.GetEnumerator()
            {
                return new ShortPrimitiveEnumerator();
            }
            #endregion
        }
        #endregion

        static public IEnumerable<ShortPrimitive> Sequence()
        {
            return new ShortPrimitiveEnumerable();
        }
    }
}

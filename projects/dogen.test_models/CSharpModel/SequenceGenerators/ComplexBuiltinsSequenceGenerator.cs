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
    /// Generates sequences of ComplexBuiltins.
    /// </summary>
    public static class ComplexBuiltinsSequenceGenerator
    {
        static internal void Populate(ComplexBuiltins value, uint position)
        {
            value.ObjectProperty = AssistantSequenceGenerator.CreateObject(position + 0);
            value.StringProperty = AssistantSequenceGenerator.CreateString(position + 1);
        }

        static internal ComplexBuiltins Create(uint position)
        {
            var result = new ComplexBuiltins();
            Populate(result, position);
            return result;
        }

        #region Enumerator
        private class ComplexBuiltinsEnumerator : IEnumerator, IEnumerator<ComplexBuiltins>, IDisposable
        {
            #region Properties
            private uint _position;
            private ComplexBuiltins _current;
            #endregion

            private void PopulateCurrent()
            {
                _current = ComplexBuiltinsSequenceGenerator.Create(_position);
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

            ComplexBuiltins IEnumerator<ComplexBuiltins>.Current
            {
                get
                {
                    return _current;
                }
            }
            #endregion

            public ComplexBuiltinsEnumerator()
            {
                PopulateCurrent();
            }
        }
        #endregion

        #region Enumerable
        private class ComplexBuiltinsEnumerable : IEnumerable, IEnumerable<ComplexBuiltins>
        {
            #region IEnumerable implementation
            public IEnumerator GetEnumerator()
            {
                return new ComplexBuiltinsEnumerator();
            }

            IEnumerator<ComplexBuiltins> IEnumerable<ComplexBuiltins>.GetEnumerator()
            {
                return new ComplexBuiltinsEnumerator();
            }
            #endregion
        }
        #endregion

        static public IEnumerable<ComplexBuiltins> Sequence()
        {
            return new ComplexBuiltinsEnumerable();
        }
    }
}

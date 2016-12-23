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
    /// Generates sequences of NonSealedLeaf.
    /// </summary>
    public static class NonSealedLeafSequenceGenerator
    {
        static internal void Populate(NonSealedLeaf value, uint position)
        {
            Dogen.TestModels.CSharpModel.Descendant1SequenceGenerator.Populate(value, position);
            value.Prop0 = AssistantSequenceGenerator.CreateInt(position + 0);
        }

        static internal NonSealedLeaf Create(uint position)
        {
            var result = new NonSealedLeaf();
            Populate(result, position);
            return result;
        }

        #region Enumerator
        private class NonSealedLeafEnumerator : IEnumerator, IEnumerator<NonSealedLeaf>, IDisposable
        {
            #region Properties
            private uint _position;
            private NonSealedLeaf _current;
            #endregion

            private void PopulateCurrent()
            {
                _current = NonSealedLeafSequenceGenerator.Create(_position);
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

            NonSealedLeaf IEnumerator<NonSealedLeaf>.Current
            {
                get
                {
                    return _current;
                }
            }
            #endregion

            public NonSealedLeafEnumerator()
            {
                PopulateCurrent();
            }
        }
        #endregion

        #region Enumerable
        private class NonSealedLeafEnumerable : IEnumerable, IEnumerable<NonSealedLeaf>
        {
            #region IEnumerable implementation
            public IEnumerator GetEnumerator()
            {
                return new NonSealedLeafEnumerator();
            }

            IEnumerator<NonSealedLeaf> IEnumerable<NonSealedLeaf>.GetEnumerator()
            {
                return new NonSealedLeafEnumerator();
            }
            #endregion
        }
        #endregion

        static public IEnumerable<NonSealedLeaf> Sequence()
        {
            return new NonSealedLeafEnumerable();
        }
    }
}

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
    /// Generates sequences of Descendant1.
    /// </summary>
    public static class Descendant1SequenceGenerator
    {
        static internal void Populate(Descendant1 value, uint position)
        {
        }
        static internal Descendant1 Create(uint position)
        {
            if ((position % 1) == 0)
                return Dogen.TestModels.CSharpModel.NonSealedLeafSequenceGenerator.Create(position);
            return Dogen.TestModels.CSharpModel.Descendant3SequenceGenerator.Create(position);
        }

        #region Enumerator
        private class Descendant1Enumerator : IEnumerator, IEnumerator<Descendant1>, IDisposable
        {
            #region Properties
            private uint _position;
            private Descendant1 _current;
            #endregion

            private void PopulateCurrent()
            {
                _current = Descendant1SequenceGenerator.Create(_position);
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

            Descendant1 IEnumerator<Descendant1>.Current
            {
                get
                {
                    return _current;
                }
            }
            #endregion

            public Descendant1Enumerator()
            {
                PopulateCurrent();
            }
        }
        #endregion

        #region Enumerable
        private class Descendant1Enumerable : IEnumerable, IEnumerable<Descendant1>
        {
            #region IEnumerable implementation
            public IEnumerator GetEnumerator()
            {
                return new Descendant1Enumerator();
            }

            IEnumerator<Descendant1> IEnumerable<Descendant1>.GetEnumerator()
            {
                return new Descendant1Enumerator();
            }
            #endregion
        }
        #endregion

        static public IEnumerable<Descendant1> Sequence()
        {
            return new Descendant1Enumerable();
        }
    }
}

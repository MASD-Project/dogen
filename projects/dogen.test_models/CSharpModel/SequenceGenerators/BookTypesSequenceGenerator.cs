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
    /// Generates sequences of BookTypes.
    /// </summary>
    public static class BookTypesSequenceGenerator
    {
        static internal BookTypes Create(uint position)
        {
            var result = (BookTypes)(position % 4);
            return result;
        }

        #region Enumerator
        private class BookTypesEnumerator : IEnumerator, IEnumerator<BookTypes>, IDisposable
        {
            #region Properties
            private uint _position;
            private BookTypes _current;
            #endregion

            private void PopulateCurrent()
            {
                _current = BookTypesSequenceGenerator.Create(_position);
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

            BookTypes IEnumerator<BookTypes>.Current
            {
                get
                {
                    return _current;
                }
            }
            #endregion

            public BookTypesEnumerator()
            {
                PopulateCurrent();
            }
        }
        #endregion

        #region Enumerable
        private class BookTypesEnumerable : IEnumerable, IEnumerable<BookTypes>
        {
            #region IEnumerable implementation
            public IEnumerator GetEnumerator()
            {
                return new BookTypesEnumerator();
            }

            IEnumerator<BookTypes> IEnumerable<BookTypes>.GetEnumerator()
            {
                return new BookTypesEnumerator();
            }
            #endregion
        }
        #endregion

        static public IEnumerable<BookTypes> Sequence()
        {
            return new BookTypesEnumerable();
        }
    }
}

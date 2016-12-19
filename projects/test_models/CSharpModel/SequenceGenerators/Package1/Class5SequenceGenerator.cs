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

namespace Dogen.TestModels.CSharpModel.Package1
{
    /// <summary>
    /// Generates sequences of Class5.
    /// </summary>
    public static class Class5SequenceGenerator
    {
        static internal Class5 Create(uint position)
        {
            var result = new Class5();

            result.Prop0 = AssistantSequenceGenerator.CreateInt(position + 0);

            return result;
        }

        #region Enumerator
        private class Class5Enumerator : IEnumerator, IEnumerator<Class5>, IDisposable
        {
            #region Properties
            private uint _position;
            private Class5 _current;
            #endregion

            private void PopulateCurrent()
            {
                _current = Class5SequenceGenerator.Create(_position);
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

            Class5 IEnumerator<Class5>.Current
            {
                get
                {
                    return _current;
                }
            }
            #endregion

            public Class5Enumerator()
            {
                PopulateCurrent();
            }
        }
        #endregion

        #region Enumerable
        private class Class5Enumerable : IEnumerable, IEnumerable<Class5>
        {
            #region IEnumerable implementation
            public IEnumerator GetEnumerator()
            {
                return new Class5Enumerator();
            }

            IEnumerator<Class5> IEnumerable<Class5>.GetEnumerator()
            {
                return new Class5Enumerator();
            }
            #endregion
        }
        #endregion

        static public IEnumerable<Class5> Sequence()
        {
            return new Class5Enumerable();
        }
    }
}

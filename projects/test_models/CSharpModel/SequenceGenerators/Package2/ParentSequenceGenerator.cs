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

namespace Dogen.TestModels.CSharpModel.Package2
{
    /// <summary>
    /// Generates sequences of Parent.
    /// </summary>
    public static class ParentSequenceGenerator
    {
        static internal void Populate(Parent value, uint position)
        {
            value.Prop0 = AssistantSequenceGenerator.CreateInt(position + 0);
        }

        static internal Parent Create(uint position)
        {
            if ((position % 1) == 0)
                return Dogen.TestModels.CSharpModel.Package2.ChildViaSettingsSequenceGenerator.Create(position);
            return Dogen.TestModels.CSharpModel.Package2.ChildSequenceGenerator.Create(position);
        }

        #region Enumerator
        private class ParentEnumerator : IEnumerator, IEnumerator<Parent>, IDisposable
        {
            #region Properties
            private uint _position;
            private Parent _current;
            #endregion

            private void PopulateCurrent()
            {
                _current = ParentSequenceGenerator.Create(_position);
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

            Parent IEnumerator<Parent>.Current
            {
                get
                {
                    return _current;
                }
            }
            #endregion

            public ParentEnumerator()
            {
                PopulateCurrent();
            }
        }
        #endregion

        #region Enumerable
        private class ParentEnumerable : IEnumerable, IEnumerable<Parent>
        {
            #region IEnumerable implementation
            public IEnumerator GetEnumerator()
            {
                return new ParentEnumerator();
            }

            IEnumerator<Parent> IEnumerable<Parent>.GetEnumerator()
            {
                return new ParentEnumerator();
            }
            #endregion
        }
        #endregion

        static public IEnumerable<Parent> Sequence()
        {
            return new ParentEnumerable();
        }
    }
}

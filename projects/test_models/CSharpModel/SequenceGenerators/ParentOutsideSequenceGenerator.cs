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
    /// Generates sequences of ParentOutside.
    /// </summary>
    public static class ParentOutsideSequenceGenerator
    {
        static internal void Populate(ParentOutside value, uint position)
        {
            value.Prop0 = AssistantSequenceGenerator.CreateInt(position + 0);
        }

        static internal ParentOutside Create(uint position)
        {
            if ((position % 1) == 0)
                return Dogen.TestModels.CSharpModel.Package5.ChildViaSettingsSequenceGenerator.Create(position);
            return Dogen.TestModels.CSharpModel.Package5.ChildSequenceGenerator.Create(position);
        }

        #region Enumerator
        private class ParentOutsideEnumerator : IEnumerator, IEnumerator<ParentOutside>, IDisposable
        {
            #region Properties
            private uint _position;
            private ParentOutside _current;
            #endregion

            private void PopulateCurrent()
            {
                _current = ParentOutsideSequenceGenerator.Create(_position);
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

            ParentOutside IEnumerator<ParentOutside>.Current
            {
                get
                {
                    return _current;
                }
            }
            #endregion

            public ParentOutsideEnumerator()
            {
                PopulateCurrent();
            }
        }
        #endregion

        #region Enumerable
        private class ParentOutsideEnumerable : IEnumerable, IEnumerable<ParentOutside>
        {
            #region IEnumerable implementation
            public IEnumerator GetEnumerator()
            {
                return new ParentOutsideEnumerator();
            }

            IEnumerator<ParentOutside> IEnumerable<ParentOutside>.GetEnumerator()
            {
                return new ParentOutsideEnumerator();
            }
            #endregion
        }
        #endregion

        static public IEnumerable<ParentOutside> Sequence()
        {
            return new ParentOutsideEnumerable();
        }
    }
}

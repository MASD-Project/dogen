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

namespace dogen.test_models.all_path_and_directory_settings.package_0.package_0_1
{
    /// <summary>
    /// Generates sequences of class_2.
    /// </summary>
    public static class class_2SequenceGenerator
    {
        static internal void Populate(class_2 value, uint position)
        {
            value.prop_0 = AssistantSequenceGenerator.CreateInt(position + 0);
        }

        static internal class_2 Create(uint position)
        {
            var result = new class_2();
            Populate(result, position);
            return result;
        }

        #region Enumerator
        private class class_2Enumerator : IEnumerator, IEnumerator<class_2>, IDisposable
        {
            #region Properties
            private uint _position;
            private class_2 _current;
            #endregion

            private void PopulateCurrent()
            {
                _current = class_2SequenceGenerator.Create(_position);
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

            class_2 IEnumerator<class_2>.Current
            {
                get
                {
                    return _current;
                }
            }
            #endregion

            public class_2Enumerator()
            {
                PopulateCurrent();
            }
        }
        #endregion

        #region Enumerable
        private class class_2Enumerable : IEnumerable, IEnumerable<class_2>
        {
            #region IEnumerable implementation
            public IEnumerator GetEnumerator()
            {
                return new class_2Enumerator();
            }

            IEnumerator<class_2> IEnumerable<class_2>.GetEnumerator()
            {
                return new class_2Enumerator();
            }
            #endregion
        }
        #endregion

        static public IEnumerable<class_2> Sequence()
        {
            return new class_2Enumerable();
        }
    }
}

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
    /// Generates sequences of ChildViaSettings.
    /// </summary>
    public static class ChildViaSettingsSequenceGenerator
    {
        static internal void Populate(ChildViaSettings value, uint position)
        {
            Dogen.TestModels.CSharpModel.Package2.ParentSequenceGenerator.Populate(value, position);
            value.Prop1 = AssistantSequenceGenerator.CreateInt(position + 0);
        }

        static internal ChildViaSettings Create(uint position)
        {
            var result = new ChildViaSettings();
            Populate(result, position);
            return result;
        }

        #region Enumerator
        private class ChildViaSettingsEnumerator : IEnumerator, IEnumerator<ChildViaSettings>, IDisposable
        {
            #region Properties
            private uint _position;
            private ChildViaSettings _current;
            #endregion

            private void PopulateCurrent()
            {
                _current = ChildViaSettingsSequenceGenerator.Create(_position);
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

            ChildViaSettings IEnumerator<ChildViaSettings>.Current
            {
                get
                {
                    return _current;
                }
            }
            #endregion

            public ChildViaSettingsEnumerator()
            {
                PopulateCurrent();
            }
        }
        #endregion

        #region Enumerable
        private class ChildViaSettingsEnumerable : IEnumerable, IEnumerable<ChildViaSettings>
        {
            #region IEnumerable implementation
            public IEnumerator GetEnumerator()
            {
                return new ChildViaSettingsEnumerator();
            }

            IEnumerator<ChildViaSettings> IEnumerable<ChildViaSettings>.GetEnumerator()
            {
                return new ChildViaSettingsEnumerator();
            }
            #endregion
        }
        #endregion

        static public IEnumerable<ChildViaSettings> Sequence()
        {
            return new ChildViaSettingsEnumerable();
        }
    }
}

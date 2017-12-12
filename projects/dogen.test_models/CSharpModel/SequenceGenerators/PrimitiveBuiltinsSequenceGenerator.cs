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
    /// Generates sequences of PrimitiveBuiltins.
    /// </summary>
    public static class PrimitiveBuiltinsSequenceGenerator
    {
        static internal void Populate(PrimitiveBuiltins value, uint position)
        {
            value.ByteProperty = AssistantSequenceGenerator.CreateByte(position + 0);
            value.ShortByteProperty = AssistantSequenceGenerator.CreateShortByte(position + 1);
            value.IntProperty = AssistantSequenceGenerator.CreateInt(position + 2);
            value.UIntProperty = AssistantSequenceGenerator.CreateUInt(position + 3);
            value.ShortProperty = AssistantSequenceGenerator.CreateShort(position + 4);
            value.UShortProperty = AssistantSequenceGenerator.CreateUShort(position + 5);
            value.LongProperty = AssistantSequenceGenerator.CreateLong(position + 6);
            value.ULongProperty = AssistantSequenceGenerator.CreateULong(position + 7);
            value.FloatPropertyOne = AssistantSequenceGenerator.CreateFloat(position + 8);
            value.FloatPropertyTwo = AssistantSequenceGenerator.CreateFloat(position + 9);
            value.DoublePropertyOne = AssistantSequenceGenerator.CreateDouble(position + 10);
            value.DoublePropertyTwo = AssistantSequenceGenerator.CreateDouble(position + 11);
            value.CharProperty = AssistantSequenceGenerator.CreateChar(position + 12);
            value.BoolProperty = AssistantSequenceGenerator.CreateBool(position + 13);
            value.DecimalProperty = AssistantSequenceGenerator.CreateDecimal(position + 14);
        }

        static internal PrimitiveBuiltins Create(uint position)
        {
            var result = new PrimitiveBuiltins();
            Populate(result, position);
            return result;
        }

        #region Enumerator
        private class PrimitiveBuiltinsEnumerator : IEnumerator, IEnumerator<PrimitiveBuiltins>, IDisposable
        {
            #region Properties
            private uint _position;
            private PrimitiveBuiltins _current;
            #endregion

            private void PopulateCurrent()
            {
                _current = PrimitiveBuiltinsSequenceGenerator.Create(_position);
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

            PrimitiveBuiltins IEnumerator<PrimitiveBuiltins>.Current
            {
                get
                {
                    return _current;
                }
            }
            #endregion

            public PrimitiveBuiltinsEnumerator()
            {
                PopulateCurrent();
            }
        }
        #endregion

        #region Enumerable
        private class PrimitiveBuiltinsEnumerable : IEnumerable, IEnumerable<PrimitiveBuiltins>
        {
            #region IEnumerable implementation
            public IEnumerator GetEnumerator()
            {
                return new PrimitiveBuiltinsEnumerator();
            }

            IEnumerator<PrimitiveBuiltins> IEnumerable<PrimitiveBuiltins>.GetEnumerator()
            {
                return new PrimitiveBuiltinsEnumerator();
            }
            #endregion
        }
        #endregion

        static public IEnumerable<PrimitiveBuiltins> Sequence()
        {
            return new PrimitiveBuiltinsEnumerable();
        }
    }
}

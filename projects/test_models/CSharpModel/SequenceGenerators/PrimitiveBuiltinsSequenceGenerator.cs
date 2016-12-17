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
        static internal PrimitiveBuiltins Create(uint position)
        {
            var result = new PrimitiveBuiltins();

            result.ByteProperty = GeneratorHelper.CreateByte(position + 0);
            result.ShortByteProperty = GeneratorHelper.CreateShortByte(position + 1);
            result.IntProperty = GeneratorHelper.CreateInt(position + 2);
            result.UIntProperty = GeneratorHelper.CreateUInt(position + 3);
            result.ShortProperty = GeneratorHelper.CreateShort(position + 4);
            result.UShortProperty = GeneratorHelper.CreateUShort(position + 5);
            result.LongProperty = GeneratorHelper.CreateLong(position + 6);
            result.ULongProperty = GeneratorHelper.CreateULong(position + 7);
            result.FloatPropertyOne = GeneratorHelper.CreateFloat(position + 8);
            result.FloatPropertyTwo = GeneratorHelper.CreateFloat(position + 9);
            result.DoublePropertyOne = GeneratorHelper.CreateDouble(position + 10);
            result.DoublePropertyTwo = GeneratorHelper.CreateDouble(position + 11);
            result.CharProperty = GeneratorHelper.CreateChar(position + 12);
            result.BoolProperty = GeneratorHelper.CreateBool(position + 13);
            result.DecimalProperty = GeneratorHelper.CreateDecimal(position + 14);

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

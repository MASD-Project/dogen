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
    /// Generates sequences of ComplexBuiltins.
    /// </summary>
    public static class ComplexBuiltinsSequenceGenerator {
        static internal ComplexBuiltins Create(uint position)
        {
            var result = new ComplexBuiltins();
            result.ObjectProperty = GeneratorHelper.CreateObject(position + 0);
            result.StringProperty = GeneratorHelper.CreateString(position + 1);
            return result;
        }

        #region Enumerator
        private class ComplexBuiltinsEnumerator : IEnumerator, IEnumerator<ComplexBuiltins>, IDisposable 
        {
            #region Properties
            private uint _position;
            private readonly ComplexBuiltins _current;
            #endregion

            #region IDisposable
            public void Dispose()
            {
            }
            #endregion

            #region IEnumerator implementation
            public bool MoveNext()
            {
                ++_position;
                Create(_position);
                return true;
            }

            public void Reset()
            {
                _position = 0;
                Create(_position);
            }

            public object Current {
                get
                {
                    return _current;
                }
            }

            ComplexBuiltins IEnumerator<ComplexBuiltins>.Current                                                
            {                                                                           
                get                                                                     
                {                                                                       
                    return _current;                                           
                }                                                                       
            }                                                                           
            #endregion

            public ComplexBuiltinsEnumerator()
            {
                _current = ComplexBuiltinsSequenceGenerator.Create(_position);
            }
        }
        #endregion

        #region Enumerable
        private class ComplexBuiltinsEnumerable : IEnumerable, IEnumerable<ComplexBuiltins>
        {
            #region IEnumerable implementation
            public IEnumerator GetEnumerator()
            {
                return new ComplexBuiltinsEnumerator();
            }

            IEnumerator<ComplexBuiltins> IEnumerable<ComplexBuiltins>.GetEnumerator()
            {
                return new ComplexBuiltinsEnumerator();
            }
            #endregion
        }
        #endregion

        static public IEnumerable<ComplexBuiltins> Sequence()
        {
            return new ComplexBuiltinsEnumerable();
        }
    }
}

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
    /// Generates sequences of AssociationInPackage.
    /// </summary>
    public static class AssociationInPackageSequenceGenerator
    {
        static internal AssociationInPackage Create(uint position)
        {
            var result = new AssociationInPackage();

            result.Prop0 = Dogen.TestModels.CSharpModel.PrimitiveBuiltinsSequenceGenerator.Create(position + 0);
            result.Prop1 = Dogen.TestModels.CSharpModel.ComplexBuiltinsSequenceGenerator.Create(position + 1);
            result.Prop2 = Dogen.TestModels.CSharpModel.Package1.Class1SequenceGenerator.Create(position + 2);

            return result;
        }

        #region Enumerator
        private class AssociationInPackageEnumerator : IEnumerator, IEnumerator<AssociationInPackage>, IDisposable
        {
            #region Properties
            private uint _position;
            private AssociationInPackage _current;
            #endregion

            private void PopulateCurrent()
            {
                _current = AssociationInPackageSequenceGenerator.Create(_position);
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

            AssociationInPackage IEnumerator<AssociationInPackage>.Current
            {
                get
                {
                    return _current;
                }
            }
            #endregion

            public AssociationInPackageEnumerator()
            {
                PopulateCurrent();
            }
        }
        #endregion

        #region Enumerable
        private class AssociationInPackageEnumerable : IEnumerable, IEnumerable<AssociationInPackage>
        {
            #region IEnumerable implementation
            public IEnumerator GetEnumerator()
            {
                return new AssociationInPackageEnumerator();
            }

            IEnumerator<AssociationInPackage> IEnumerable<AssociationInPackage>.GetEnumerator()
            {
                return new AssociationInPackageEnumerator();
            }
            #endregion
        }
        #endregion

        static public IEnumerable<AssociationInPackage> Sequence()
        {
            return new AssociationInPackageEnumerable();
        }
    }
}

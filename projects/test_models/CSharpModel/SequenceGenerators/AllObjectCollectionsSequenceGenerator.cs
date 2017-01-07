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
    /// Generates sequences of AllObjectCollections.
    /// </summary>
    public static class AllObjectCollectionsSequenceGenerator
    {
        static internal void Populate(AllObjectCollections value, uint position)
        {
            value.Prop0 = AssistantSequenceGenerator.CreateArrayList(position + 0);
            value.Prop1 = AssistantSequenceGenerator.CreateIEnumerable(position + 1);
            value.Prop2 = AssistantSequenceGenerator.CreateICollection(position + 2);
            value.Prop3 = AssistantSequenceGenerator.CreateIList(position + 3);
            value.Prop4 = AssistantSequenceGenerator.CreateHashtable(position + 4);
            value.Prop5 = AssistantSequenceGenerator.CreateIDictionary(position + 5);
            value.Prop6 = AssistantSequenceGenerator.CreateHybridDictionary(position + 6);
            value.Prop7 = AssistantSequenceGenerator.CreateNameValueCollection(position + 7);
            value.Prop8 = AssistantSequenceGenerator.CreateBitArray(position + 8);
        }

        static internal AllObjectCollections Create(uint position)
        {
            var result = new AllObjectCollections();
            Populate(result, position);
            return result;
        }

        #region Enumerator
        private class AllObjectCollectionsEnumerator : IEnumerator, IEnumerator<AllObjectCollections>, IDisposable
        {
            #region Properties
            private uint _position;
            private AllObjectCollections _current;
            #endregion

            private void PopulateCurrent()
            {
                _current = AllObjectCollectionsSequenceGenerator.Create(_position);
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

            AllObjectCollections IEnumerator<AllObjectCollections>.Current
            {
                get
                {
                    return _current;
                }
            }
            #endregion

            public AllObjectCollectionsEnumerator()
            {
                PopulateCurrent();
            }
        }
        #endregion

        #region Enumerable
        private class AllObjectCollectionsEnumerable : IEnumerable, IEnumerable<AllObjectCollections>
        {
            #region IEnumerable implementation
            public IEnumerator GetEnumerator()
            {
                return new AllObjectCollectionsEnumerator();
            }

            IEnumerator<AllObjectCollections> IEnumerable<AllObjectCollections>.GetEnumerator()
            {
                return new AllObjectCollectionsEnumerator();
            }
            #endregion
        }
        #endregion

        static public IEnumerable<AllObjectCollections> Sequence()
        {
            return new AllObjectCollectionsEnumerable();
        }
    }
}

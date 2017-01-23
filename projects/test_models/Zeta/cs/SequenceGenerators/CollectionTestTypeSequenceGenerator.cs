using System;
using System.Collections;
using System.Collections.Generic;

namespace Phi
{
    /// <summary>
    /// Generates sequences of CollectionTestType.
    /// </summary>
    public static class CollectionTestTypeSequenceGenerator
    {
        static internal void Populate(CollectionTestType value, uint position)
        {
            value.BinariesTest = System.Collections.Generic.ListSequenceGenerator.Create(position + 0);
        }

        static internal CollectionTestType Create(uint position)
        {
            var result = new CollectionTestType();
            Populate(result, position);
            return result;
        }

        #region Enumerator
        private class CollectionTestTypeEnumerator : IEnumerator, IEnumerator<CollectionTestType>, IDisposable
        {
            #region Properties
            private uint _position;
            private CollectionTestType _current;
            #endregion

            private void PopulateCurrent()
            {
                _current = CollectionTestTypeSequenceGenerator.Create(_position);
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

            CollectionTestType IEnumerator<CollectionTestType>.Current
            {
                get
                {
                    return _current;
                }
            }
            #endregion

            public CollectionTestTypeEnumerator()
            {
                PopulateCurrent();
            }
        }
        #endregion

        #region Enumerable
        private class CollectionTestTypeEnumerable : IEnumerable, IEnumerable<CollectionTestType>
        {
            #region IEnumerable implementation
            public IEnumerator GetEnumerator()
            {
                return new CollectionTestTypeEnumerator();
            }

            IEnumerator<CollectionTestType> IEnumerable<CollectionTestType>.GetEnumerator()
            {
                return new CollectionTestTypeEnumerator();
            }
            #endregion
        }
        #endregion

        static public IEnumerable<CollectionTestType> Sequence()
        {
            return new CollectionTestTypeEnumerable();
        }
    }
}

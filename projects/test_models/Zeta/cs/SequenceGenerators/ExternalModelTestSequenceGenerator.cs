using System;
using System.Collections;
using System.Collections.Generic;

namespace Zeta
{
    /// <summary>
    /// Generates sequences of ExternalModelTest.
    /// </summary>
    public static class ExternalModelTestSequenceGenerator
    {
        static internal void Populate(ExternalModelTest value, uint position)
        {
            value.DateTest = Phi.DateSequenceGenerator.Create(position + 0);
            value.BinariesTest = System.Collections.Generic.ArraySequenceGenerator.Create(position + 1);
            value.CollectionOfCollectionTest = System.Collections.Generic.ArraySequenceGenerator.Create(position + 2);
            value.CollectionOfCollectionOfCollectionTest = System.Collections.Generic.ArraySequenceGenerator.Create(position + 3);
        }

        static internal ExternalModelTest Create(uint position)
        {
            var result = new ExternalModelTest();
            Populate(result, position);
            return result;
        }

        #region Enumerator
        private class ExternalModelTestEnumerator : IEnumerator, IEnumerator<ExternalModelTest>, IDisposable
        {
            #region Properties
            private uint _position;
            private ExternalModelTest _current;
            #endregion

            private void PopulateCurrent()
            {
                _current = ExternalModelTestSequenceGenerator.Create(_position);
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

            ExternalModelTest IEnumerator<ExternalModelTest>.Current
            {
                get
                {
                    return _current;
                }
            }
            #endregion

            public ExternalModelTestEnumerator()
            {
                PopulateCurrent();
            }
        }
        #endregion

        #region Enumerable
        private class ExternalModelTestEnumerable : IEnumerable, IEnumerable<ExternalModelTest>
        {
            #region IEnumerable implementation
            public IEnumerator GetEnumerator()
            {
                return new ExternalModelTestEnumerator();
            }

            IEnumerator<ExternalModelTest> IEnumerable<ExternalModelTest>.GetEnumerator()
            {
                return new ExternalModelTestEnumerator();
            }
            #endregion
        }
        #endregion

        static public IEnumerable<ExternalModelTest> Sequence()
        {
            return new ExternalModelTestEnumerable();
        }
    }
}

using System;
using System.Collections;
using System.Collections.Generic;

namespace Phi
{
    /// <summary>
    /// Generates sequences of TestType.
    /// </summary>
    public static class TestTypeSequenceGenerator
    {
        static internal void Populate(TestType value, uint position)
        {
            value.Version = Zeta.StringSequenceGenerator.Create(position + 0);
            value.AField = Zeta.StringSequenceGenerator.Create(position + 1);
        }

        static internal TestType Create(uint position)
        {
            var result = new TestType();
            Populate(result, position);
            return result;
        }

        #region Enumerator
        private class TestTypeEnumerator : IEnumerator, IEnumerator<TestType>, IDisposable
        {
            #region Properties
            private uint _position;
            private TestType _current;
            #endregion

            private void PopulateCurrent()
            {
                _current = TestTypeSequenceGenerator.Create(_position);
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

            TestType IEnumerator<TestType>.Current
            {
                get
                {
                    return _current;
                }
            }
            #endregion

            public TestTypeEnumerator()
            {
                PopulateCurrent();
            }
        }
        #endregion

        #region Enumerable
        private class TestTypeEnumerable : IEnumerable, IEnumerable<TestType>
        {
            #region IEnumerable implementation
            public IEnumerator GetEnumerator()
            {
                return new TestTypeEnumerator();
            }

            IEnumerator<TestType> IEnumerable<TestType>.GetEnumerator()
            {
                return new TestTypeEnumerator();
            }
            #endregion
        }
        #endregion

        static public IEnumerable<TestType> Sequence()
        {
            return new TestTypeEnumerable();
        }
    }
}

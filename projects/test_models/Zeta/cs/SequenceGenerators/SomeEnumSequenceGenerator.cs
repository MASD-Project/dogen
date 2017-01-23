using System;
using System.Collections;
using System.Collections.Generic;

namespace Phi
{
    /// <summary>
    /// Generates sequences of SomeEnum.
    /// </summary>
    public static class SomeEnumSequenceGenerator
    {
        static internal SomeEnum Create(uint position)
        {
            var result = (SomeEnum)(position % 1);
            return result;
        }

        #region Enumerator
        private class SomeEnumEnumerator : IEnumerator, IEnumerator<SomeEnum>, IDisposable
        {
            #region Properties
            private uint _position;
            private SomeEnum _current;
            #endregion

            private void PopulateCurrent()
            {
                _current = SomeEnumSequenceGenerator.Create(_position);
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

            SomeEnum IEnumerator<SomeEnum>.Current
            {
                get
                {
                    return _current;
                }
            }
            #endregion

            public SomeEnumEnumerator()
            {
                PopulateCurrent();
            }
        }
        #endregion

        #region Enumerable
        private class SomeEnumEnumerable : IEnumerable, IEnumerable<SomeEnum>
        {
            #region IEnumerable implementation
            public IEnumerator GetEnumerator()
            {
                return new SomeEnumEnumerator();
            }

            IEnumerator<SomeEnum> IEnumerable<SomeEnum>.GetEnumerator()
            {
                return new SomeEnumEnumerator();
            }
            #endregion
        }
        #endregion

        static public IEnumerable<SomeEnum> Sequence()
        {
            return new SomeEnumEnumerable();
        }
    }
}

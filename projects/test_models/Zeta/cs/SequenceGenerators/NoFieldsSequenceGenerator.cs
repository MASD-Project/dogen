using System;
using System.Collections;
using System.Collections.Generic;

namespace Phi
{
    /// <summary>
    /// Generates sequences of NoFields.
    /// </summary>
    public static class NoFieldsSequenceGenerator
    {
        static internal void Populate(NoFields value, uint position)
        {
            // nothing to populate
        }

        static internal NoFields Create(uint position)
        {
            var result = new NoFields();
            return result;
        }

        #region Enumerator
        private class NoFieldsEnumerator : IEnumerator, IEnumerator<NoFields>, IDisposable
        {
            #region Properties
            private uint _position;
            private NoFields _current;
            #endregion

            private void PopulateCurrent()
            {
                _current = NoFieldsSequenceGenerator.Create(_position);
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

            NoFields IEnumerator<NoFields>.Current
            {
                get
                {
                    return _current;
                }
            }
            #endregion

            public NoFieldsEnumerator()
            {
                PopulateCurrent();
            }
        }
        #endregion

        #region Enumerable
        private class NoFieldsEnumerable : IEnumerable, IEnumerable<NoFields>
        {
            #region IEnumerable implementation
            public IEnumerator GetEnumerator()
            {
                return new NoFieldsEnumerator();
            }

            IEnumerator<NoFields> IEnumerable<NoFields>.GetEnumerator()
            {
                return new NoFieldsEnumerator();
            }
            #endregion
        }
        #endregion

        static public IEnumerable<NoFields> Sequence()
        {
            return new NoFieldsEnumerable();
        }
    }
}

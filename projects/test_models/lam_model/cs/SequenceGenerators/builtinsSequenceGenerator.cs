using System;
using System.Collections;
using System.Collections.Generic;

namespace dogen.test_models.lam_model
{
    /// <summary>
    /// Generates sequences of builtins.
    /// </summary>
    public static class builtinsSequenceGenerator
    {
        static internal void Populate(builtins value, uint position)
        {
            value.prop_0 = AssistantSequenceGenerator.CreateChar(position + 0);
            value.prop_1 = AssistantSequenceGenerator.CreateByte(position + 1);
            value.prop_2 = AssistantSequenceGenerator.CreateShortByte(position + 2);
            value.prop_3 = AssistantSequenceGenerator.CreateInt(position + 3);
            value.prop_4 = AssistantSequenceGenerator.CreateInt(position + 4);
            value.prop_5 = AssistantSequenceGenerator.CreateInt(position + 5);
            value.prop_6 = AssistantSequenceGenerator.CreateInt(position + 6);
            value.prop_7 = AssistantSequenceGenerator.CreateFloat(position + 7);
            value.prop_8 = AssistantSequenceGenerator.CreateDouble(position + 8);
            value.prop_9 = AssistantSequenceGenerator.CreateBool(position + 9);
        }

        static internal builtins Create(uint position)
        {
            var result = new builtins();
            Populate(result, position);
            return result;
        }

        #region Enumerator
        private class builtinsEnumerator : IEnumerator, IEnumerator<builtins>, IDisposable
        {
            #region Properties
            private uint _position;
            private builtins _current;
            #endregion

            private void PopulateCurrent()
            {
                _current = builtinsSequenceGenerator.Create(_position);
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

            builtins IEnumerator<builtins>.Current
            {
                get
                {
                    return _current;
                }
            }
            #endregion

            public builtinsEnumerator()
            {
                PopulateCurrent();
            }
        }
        #endregion

        #region Enumerable
        private class builtinsEnumerable : IEnumerable, IEnumerable<builtins>
        {
            #region IEnumerable implementation
            public IEnumerator GetEnumerator()
            {
                return new builtinsEnumerator();
            }

            IEnumerator<builtins> IEnumerable<builtins>.GetEnumerator()
            {
                return new builtinsEnumerator();
            }
            #endregion
        }
        #endregion

        static public IEnumerable<builtins> Sequence()
        {
            return new builtinsEnumerable();
        }
    }
}

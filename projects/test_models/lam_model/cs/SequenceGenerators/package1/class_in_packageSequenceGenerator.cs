using System;
using System.Collections;
using System.Collections.Generic;

namespace dogen.test_models.lam_model.package1
{
    /// <summary>
    /// Generates sequences of class_in_package.
    /// </summary>
    public static class class_in_packageSequenceGenerator
    {
        static internal void Populate(class_in_package value, uint position)
        {
            value.prop_0 = AssistantSequenceGenerator.CreateInt(position + 0);
        }

        static internal class_in_package Create(uint position)
        {
            var result = new class_in_package();
            Populate(result, position);
            return result;
        }

        #region Enumerator
        private class class_in_packageEnumerator : IEnumerator, IEnumerator<class_in_package>, IDisposable
        {
            #region Properties
            private uint _position;
            private class_in_package _current;
            #endregion

            private void PopulateCurrent()
            {
                _current = class_in_packageSequenceGenerator.Create(_position);
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

            class_in_package IEnumerator<class_in_package>.Current
            {
                get
                {
                    return _current;
                }
            }
            #endregion

            public class_in_packageEnumerator()
            {
                PopulateCurrent();
            }
        }
        #endregion

        #region Enumerable
        private class class_in_packageEnumerable : IEnumerable, IEnumerable<class_in_package>
        {
            #region IEnumerable implementation
            public IEnumerator GetEnumerator()
            {
                return new class_in_packageEnumerator();
            }

            IEnumerator<class_in_package> IEnumerable<class_in_package>.GetEnumerator()
            {
                return new class_in_packageEnumerator();
            }
            #endregion
        }
        #endregion

        static public IEnumerable<class_in_package> Sequence()
        {
            return new class_in_packageEnumerable();
        }
    }
}

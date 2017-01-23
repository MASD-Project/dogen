using System;

namespace Phi
{
    /// <summary>
    /// Test type
    /// </summary>
    public sealed class CollectionTestType
    {
        #region Properties
        /// <summary>
        /// Some comment
        /// </summary>
        public System.Collections.Generic.List<object> BinariesTest { get; set; }
        #endregion

        #region Constructors
        public CollectionTestType() { }
        public CollectionTestType(System.Collections.Generic.List<object> binariesTest)
        {
            BinariesTest = binariesTest;
        }
        #endregion

        #region Equality
        public override bool Equals(object obj)
        {
            if (ReferenceEquals(null, obj)) return false;
            if (ReferenceEquals(this, obj)) return true;
            if (obj.GetType() != GetType()) return false;

            var value = obj as CollectionTestType;
            if (value == null) return false;

            return
                BinariesTest != null && value.BinariesTest != null &&
                BinariesTest.Equals(value.BinariesTest);
        }

        public static bool operator ==(CollectionTestType lhs, CollectionTestType rhs)
        {
            if (Object.ReferenceEquals(lhs, rhs))
                return true;

            return !Object.ReferenceEquals(null, lhs) && lhs.Equals(rhs);
        }

        public static bool operator !=(CollectionTestType lhs, CollectionTestType rhs)
        {
            return !(lhs == rhs);
        }

        public override int GetHashCode()
        {
            unchecked
            {
                // Choose large primes to avoid hashing collisions
                const int HashingBase = (int) 2166136261;
                const int HashingMultiplier = 16777619;

                int hash = HashingBase;
                hash = (hash * HashingMultiplier) ^
                    (!object.ReferenceEquals(null, BinariesTest) ? BinariesTest.GetHashCode() : 0);
                return hash;
            }
        }
        #endregion
    }
}

using System;

namespace Phi
{
    /// <summary>
    /// Test type
    /// </summary>
    public sealed class TestType
    {
        #region Properties
        /// <summary>
        /// Some comment
        /// </summary>
        public Zeta.String Version { get; set; }
        public Zeta.String AField { get; set; }
        #endregion

        #region Constructors
        public TestType() { }

        public TestType(
            Zeta.String version,
            Zeta.String aField)
        {
            Version = version;
            AField = aField;
        }
        #endregion

        #region Equality
        public override bool Equals(object obj)
        {
            if (ReferenceEquals(null, obj)) return false;
            if (ReferenceEquals(this, obj)) return true;
            if (obj.GetType() != GetType()) return false;

            var value = obj as TestType;
            if (value == null) return false;

            return
                Version == value.Version &&
                AField == value.AField;
        }

        public static bool operator ==(TestType lhs, TestType rhs)
        {
            if (Object.ReferenceEquals(lhs, rhs))
                return true;

            return !Object.ReferenceEquals(null, lhs) && lhs.Equals(rhs);
        }

        public static bool operator !=(TestType lhs, TestType rhs)
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
                hash = (hash * HashingMultiplier) ^ Version.GetHashCode();
                hash = (hash * HashingMultiplier) ^ AField.GetHashCode();
                return hash;
            }
        }
        #endregion
    }
}

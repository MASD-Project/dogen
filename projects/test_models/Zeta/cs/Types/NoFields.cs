using System;

namespace Phi
{
    /// <summary>
    /// Test type
    /// </summary>
    public sealed class NoFields
    {
        #region Constructors
        public NoFields() { }
        #endregion

        #region Equality
        public override bool Equals(object obj)
        {
            if (ReferenceEquals(null, obj)) return false;
            if (ReferenceEquals(this, obj)) return true;
            if (obj.GetType() != GetType()) return false;

            var value = obj as NoFields;
            return value != null;
        }

        public static bool operator ==(NoFields lhs, NoFields rhs)
        {
            if (Object.ReferenceEquals(lhs, rhs))
                return true;

            return !Object.ReferenceEquals(null, lhs) && lhs.Equals(rhs);
        }

        public static bool operator !=(NoFields lhs, NoFields rhs)
        {
            return !(lhs == rhs);
        }

        public override int GetHashCode()
        {
            return 0;
        }
        #endregion
    }
}

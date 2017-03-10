using System;

namespace dogen.test_models.lam_model.package1
{
    public sealed class class_in_package
    {
        #region Properties
        public int prop_0 { get; set; }
        #endregion

        #region Constructors
        public class_in_package() { }
        public class_in_package(int prop_0)
        {
            prop_0 = prop_0;
        }
        #endregion

        #region Equality
        public override bool Equals(object obj)
        {
            if (ReferenceEquals(null, obj)) return false;
            if (ReferenceEquals(this, obj)) return true;
            if (obj.GetType() != GetType()) return false;

            var value = obj as class_in_package;
            if (value == null) return false;

            return
                prop_0 == value.prop_0;
        }

        public static bool operator ==(class_in_package lhs, class_in_package rhs)
        {
            if (Object.ReferenceEquals(lhs, rhs))
                return true;

            return !Object.ReferenceEquals(null, lhs) && lhs.Equals(rhs);
        }

        public static bool operator !=(class_in_package lhs, class_in_package rhs)
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
                hash = (hash * HashingMultiplier) ^ prop_0.GetHashCode();
                return hash;
            }
        }
        #endregion
    }
}

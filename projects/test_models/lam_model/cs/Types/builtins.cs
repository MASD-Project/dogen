using System;

namespace dogen.test_models.lam_model
{
    public sealed class builtins
    {
        #region Helpers
        /// <summary>
        /// Compare floating point numbers, taking precision into account (float version).
        /// </summary>
        static private bool NearlyEqual(float lhs, float rhs)
        {
            float epsilon = Math.Max(Math.Abs(lhs), Math.Abs(rhs)) * float.Epsilon;
            return Math.Abs(lhs - rhs) <= epsilon;
        }
        /// <summary>
        /// Compare floating point numbers, taking precision into account (double version).
        /// </summary>
        static private bool NearlyEqual(double lhs, double rhs)
        {
            double epsilon = Math.Max(Math.Abs(lhs), Math.Abs(rhs)) * double.Epsilon;
            return Math.Abs(lhs - rhs) <= epsilon;
        }
        #endregion

        #region Properties
        public char prop_0 { get; set; }
        public byte prop_1 { get; set; }
        public sbyte prop_2 { get; set; }
        public System.Int16 prop_3 { get; set; }
        public System.Int32 prop_4 { get; set; }
        public System.Int64 prop_5 { get; set; }
        public int prop_6 { get; set; }
        public float prop_7 { get; set; }
        public double prop_8 { get; set; }
        public bool prop_9 { get; set; }
        #endregion

        #region Constructors
        public builtins() { }

        public builtins(
            char prop_0,
            byte prop_1,
            sbyte prop_2,
            System.Int16 prop_3,
            System.Int32 prop_4,
            System.Int64 prop_5,
            int prop_6,
            float prop_7,
            double prop_8,
            bool prop_9)
        {
            prop_0 = prop_0;
            prop_1 = prop_1;
            prop_2 = prop_2;
            prop_3 = prop_3;
            prop_4 = prop_4;
            prop_5 = prop_5;
            prop_6 = prop_6;
            prop_7 = prop_7;
            prop_8 = prop_8;
            prop_9 = prop_9;
        }
        #endregion

        #region Equality
        public override bool Equals(object obj)
        {
            if (ReferenceEquals(null, obj)) return false;
            if (ReferenceEquals(this, obj)) return true;
            if (obj.GetType() != GetType()) return false;

            var value = obj as builtins;
            if (value == null) return false;

            return
                prop_0 == value.prop_0 &&
                prop_1 == value.prop_1 &&
                prop_2 == value.prop_2 &&
                prop_3 == value.prop_3 &&
                prop_4 == value.prop_4 &&
                prop_5 == value.prop_5 &&
                prop_6 == value.prop_6 &&
                NearlyEqual(prop_7, value.prop_7) &&
                NearlyEqual(prop_8, value.prop_8) &&
                prop_9 == value.prop_9;
        }

        public static bool operator ==(builtins lhs, builtins rhs)
        {
            if (Object.ReferenceEquals(lhs, rhs))
                return true;

            return !Object.ReferenceEquals(null, lhs) && lhs.Equals(rhs);
        }

        public static bool operator !=(builtins lhs, builtins rhs)
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
                hash = (hash * HashingMultiplier) ^ prop_1.GetHashCode();
                hash = (hash * HashingMultiplier) ^ prop_2.GetHashCode();
                hash = (hash * HashingMultiplier) ^ prop_3.GetHashCode();
                hash = (hash * HashingMultiplier) ^ prop_4.GetHashCode();
                hash = (hash * HashingMultiplier) ^ prop_5.GetHashCode();
                hash = (hash * HashingMultiplier) ^ prop_6.GetHashCode();
                hash = (hash * HashingMultiplier) ^ prop_7.GetHashCode();
                hash = (hash * HashingMultiplier) ^ prop_8.GetHashCode();
                hash = (hash * HashingMultiplier) ^ prop_9.GetHashCode();
                return hash;
            }
        }
        #endregion
    }
}

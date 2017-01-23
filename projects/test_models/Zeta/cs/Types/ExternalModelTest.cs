using System;

namespace Zeta
{
    /// <summary>
    /// Test type
    /// </summary>
    public sealed class ExternalModelTest
    {
        #region Properties
        /// <summary>
        /// Some comment
        /// </summary>
        public Phi.Date DateTest { get; set; }
        /// <summary>
        /// Some comment
        /// </summary>
        public System.Collections.Generic.List<object> BinariesTest { get; set; }
        /// <summary>
        /// Some comment
        /// </summary>
        public System.Collections.Generic.List<System.Collections.Generic.List<object> > CollectionOfCollectionTest { get; set; }
        /// <summary>
        /// Some comment
        /// </summary>
        public System.Collections.Generic.List<System.Collections.Generic.List<System.Collections.Generic.List<object> > > CollectionOfCollectionOfCollectionTest { get; set; }
        #endregion

        #region Constructors
        public ExternalModelTest() { }

        public ExternalModelTest(
            Phi.Date dateTest,
            System.Collections.Generic.List<object> binariesTest,
            System.Collections.Generic.List<System.Collections.Generic.List<object> > collectionOfCollectionTest,
            System.Collections.Generic.List<System.Collections.Generic.List<System.Collections.Generic.List<object> > > collectionOfCollectionOfCollectionTest)
        {
            DateTest = dateTest;
            BinariesTest = binariesTest;
            CollectionOfCollectionTest = collectionOfCollectionTest;
            CollectionOfCollectionOfCollectionTest = collectionOfCollectionOfCollectionTest;
        }
        #endregion

        #region Equality
        public override bool Equals(object obj)
        {
            if (ReferenceEquals(null, obj)) return false;
            if (ReferenceEquals(this, obj)) return true;
            if (obj.GetType() != GetType()) return false;

            var value = obj as ExternalModelTest;
            if (value == null) return false;

            return
                DateTest == value.DateTest &&
                BinariesTest != null && value.BinariesTest != null &&
                BinariesTest.Equals(value.BinariesTest) &&
                CollectionOfCollectionTest != null && value.CollectionOfCollectionTest != null &&
                CollectionOfCollectionTest.Equals(value.CollectionOfCollectionTest) &&
                CollectionOfCollectionOfCollectionTest != null && value.CollectionOfCollectionOfCollectionTest != null &&
                CollectionOfCollectionOfCollectionTest.Equals(value.CollectionOfCollectionOfCollectionTest);
        }

        public static bool operator ==(ExternalModelTest lhs, ExternalModelTest rhs)
        {
            if (Object.ReferenceEquals(lhs, rhs))
                return true;

            return !Object.ReferenceEquals(null, lhs) && lhs.Equals(rhs);
        }

        public static bool operator !=(ExternalModelTest lhs, ExternalModelTest rhs)
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
                hash = (hash * HashingMultiplier) ^ DateTest.GetHashCode();
                hash = (hash * HashingMultiplier) ^
                    (!object.ReferenceEquals(null, BinariesTest) ? BinariesTest.GetHashCode() : 0);
                hash = (hash * HashingMultiplier) ^
                    (!object.ReferenceEquals(null, CollectionOfCollectionTest) ? CollectionOfCollectionTest.GetHashCode() : 0);
                hash = (hash * HashingMultiplier) ^
                    (!object.ReferenceEquals(null, CollectionOfCollectionOfCollectionTest) ? CollectionOfCollectionOfCollectionTest.GetHashCode() : 0);
                return hash;
            }
        }
        #endregion
    }
}

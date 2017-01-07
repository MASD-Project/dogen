// -*- mode: csharp; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
//
// Copyright (C) 2012-2015 Marco Craveiro <marco.craveiro@gmail.com>
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
// MA 02110-1301, USA.
//
using System;

namespace Dogen.TestModels.CSharpModel
{
    public sealed class AllObjectCollections
    {
        #region Properties
        public System.Collections.ArrayList Prop0 { get; set; }
        public System.Collections.IEnumerable Prop1 { get; set; }
        public System.Collections.ICollection Prop2 { get; set; }
        public System.Collections.IList Prop3 { get; set; }
        public System.Collections.Hashtable Prop4 { get; set; }
        public System.Collections.IDictionary Prop5 { get; set; }
        public System.Collections.Specialized.HybridDictionary Prop6 { get; set; }
        public System.Collections.Specialized.NameValueCollection Prop7 { get; set; }
        public System.Collections.BitArray Prop8 { get; set; }
        public System.Collections.Queue Prop9 { get; set; }
        public System.Collections.Stack Prop10 { get; set; }
        #endregion

        #region Constructors
        public AllObjectCollections() { }

        public AllObjectCollections(
            System.Collections.ArrayList prop0,
            System.Collections.IEnumerable prop1,
            System.Collections.ICollection prop2,
            System.Collections.IList prop3,
            System.Collections.Hashtable prop4,
            System.Collections.IDictionary prop5,
            System.Collections.Specialized.HybridDictionary prop6,
            System.Collections.Specialized.NameValueCollection prop7,
            System.Collections.BitArray prop8,
            System.Collections.Queue prop9,
            System.Collections.Stack prop10)
        {
            Prop0 = prop0;
            Prop1 = prop1;
            Prop2 = prop2;
            Prop3 = prop3;
            Prop4 = prop4;
            Prop5 = prop5;
            Prop6 = prop6;
            Prop7 = prop7;
            Prop8 = prop8;
            Prop9 = prop9;
            Prop10 = prop10;
        }
        #endregion

        #region Equality
        public override bool Equals(object obj)
        {
            if (ReferenceEquals(null, obj)) return false;
            if (ReferenceEquals(this, obj)) return true;
            if (obj.GetType() != GetType()) return false;

            var value = obj as AllObjectCollections;
            if (value == null) return false;

            return
                Prop0 != null && value.Prop0 != null &&
                Prop0.Equals(value.Prop0) &&
                Prop1 != null && value.Prop1 != null &&
                Prop1.Equals(value.Prop1) &&
                Prop2 != null && value.Prop2 != null &&
                Prop2.Equals(value.Prop2) &&
                Prop3 != null && value.Prop3 != null &&
                Prop3.Equals(value.Prop3) &&
                Prop4 != null && value.Prop4 != null &&
                Prop4.Equals(value.Prop4) &&
                Prop5 != null && value.Prop5 != null &&
                Prop5.Equals(value.Prop5) &&
                Prop6 != null && value.Prop6 != null &&
                Prop6.Equals(value.Prop6) &&
                Prop7 != null && value.Prop7 != null &&
                Prop7.Equals(value.Prop7) &&
                Prop8 != null && value.Prop8 != null &&
                Prop8.Equals(value.Prop8) &&
                Prop9 != null && value.Prop9 != null &&
                Prop9.Equals(value.Prop9) &&
                Prop10 != null && value.Prop10 != null &&
                Prop10.Equals(value.Prop10);
        }

        public static bool operator ==(AllObjectCollections lhs, AllObjectCollections rhs)
        {
            if (Object.ReferenceEquals(lhs, rhs))
                return true;

            return !Object.ReferenceEquals(null, lhs) && lhs.Equals(rhs);
        }

        public static bool operator !=(AllObjectCollections lhs, AllObjectCollections rhs)
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
                    (!object.ReferenceEquals(null, Prop0) ? Prop0.GetHashCode() : 0);
                hash = (hash * HashingMultiplier) ^
                    (!object.ReferenceEquals(null, Prop1) ? Prop1.GetHashCode() : 0);
                hash = (hash * HashingMultiplier) ^
                    (!object.ReferenceEquals(null, Prop2) ? Prop2.GetHashCode() : 0);
                hash = (hash * HashingMultiplier) ^
                    (!object.ReferenceEquals(null, Prop3) ? Prop3.GetHashCode() : 0);
                hash = (hash * HashingMultiplier) ^
                    (!object.ReferenceEquals(null, Prop4) ? Prop4.GetHashCode() : 0);
                hash = (hash * HashingMultiplier) ^
                    (!object.ReferenceEquals(null, Prop5) ? Prop5.GetHashCode() : 0);
                hash = (hash * HashingMultiplier) ^
                    (!object.ReferenceEquals(null, Prop6) ? Prop6.GetHashCode() : 0);
                hash = (hash * HashingMultiplier) ^
                    (!object.ReferenceEquals(null, Prop7) ? Prop7.GetHashCode() : 0);
                hash = (hash * HashingMultiplier) ^
                    (!object.ReferenceEquals(null, Prop8) ? Prop8.GetHashCode() : 0);
                hash = (hash * HashingMultiplier) ^
                    (!object.ReferenceEquals(null, Prop9) ? Prop9.GetHashCode() : 0);
                hash = (hash * HashingMultiplier) ^
                    (!object.ReferenceEquals(null, Prop10) ? Prop10.GetHashCode() : 0);
                return hash;
            }
        }
        #endregion
    }
}

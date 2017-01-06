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
        #endregion

        #region Constructors
        public AllObjectCollections() { }

        public AllObjectCollections(
            System.Collections.ArrayList prop0,
            System.Collections.IEnumerable prop1,
            System.Collections.ICollection prop2,
            System.Collections.IList prop3)
        {
            Prop0 = prop0;
            Prop1 = prop1;
            Prop2 = prop2;
            Prop3 = prop3;
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
                Prop3.Equals(value.Prop3);
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
                return hash;
            }
        }
        #endregion
    }
}

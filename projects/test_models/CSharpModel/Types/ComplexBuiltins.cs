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
    /// <summary>
    /// This is a class made up of just complex builtin types.
    /// </summary>
    /// <remarks>
    /// This is a remark.
    /// </remarks>
	public class ComplexBuiltins
    {
		#region Properties
        public object ObjectProperty { get; set; }
        public string StringProperty { get; set; }
        #endregion

        #region Equality
        public override bool Equals(object obj)
        {
            if (ReferenceEquals(null, obj)) return false;
            if (ReferenceEquals(this, obj)) return true;
            if (obj.GetType() != GetType()) return false;

            var value = obj as ComplexBuiltins;
            if (value == null) return false;

            return
                ObjectProperty != null && value.ObjectProperty != null &&
                ObjectProperty.Equals(value.ObjectProperty) &&
                StringProperty != null && value.StringProperty != null &&
                StringProperty.Equals(value.StringProperty);
        }

        public static bool operator ==(ComplexBuiltins lhs, ComplexBuiltins rhs)
        {
            if (Object.ReferenceEquals(lhs, rhs))
                return true;

            if(Object.ReferenceEquals(null, lhs))
                return false;

            return lhs.Equals(rhs);
        }

        public static bool operator !=(ComplexBuiltins lhs, ComplexBuiltins rhs)
        {
            return !(lhs == rhs);
        }

        public override int GetHashCode()
		{
			unchecked {
				// Choose large primes to avoid hashing collisions
				const int HashingBase = (int)2166136261;
				const int HashingMultiplier = 16777619;

				int hash = HashingBase;
				hash = (hash * HashingMultiplier) ^
				(!object.ReferenceEquals(null, ObjectProperty) ? ObjectProperty.GetHashCode() : 0);
				hash = (hash * HashingMultiplier) ^
				(!object.ReferenceEquals(null, StringProperty) ? StringProperty.GetHashCode() : 0);
				return hash;
			}
		}
 		#endregion
    }
}

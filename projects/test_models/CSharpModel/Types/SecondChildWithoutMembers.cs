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
    public sealed class SecondChildWithoutMembers : Dogen.TestModels.CSharpModel.ParentWithMembers
    {
        #region Equality
        public override bool Equals(object obj)
        {
            if (ReferenceEquals(null, obj)) return false;
            if (ReferenceEquals(this, obj)) return true;
            if (obj.GetType() != GetType()) return false;

            var value = obj as SecondChildWithoutMembers;
            return (value != null && base.Equals(value));
        }

        public static bool operator ==(SecondChildWithoutMembers lhs, SecondChildWithoutMembers rhs)
        {
            if (Object.ReferenceEquals(lhs, rhs))
                return true;

            return !Object.ReferenceEquals(null, lhs) && lhs.Equals(rhs);
        }

        public static bool operator !=(SecondChildWithoutMembers lhs, SecondChildWithoutMembers rhs)
        {
            return !(lhs == rhs);
        }

        public override int GetHashCode()
        {
            return 0;
        }
        #endregion

        #region Dumpers
        internal override string Dump()
        {
            return SecondChildWithoutMembersDumper.Dump(this);
        }
        #endregion
    }
}

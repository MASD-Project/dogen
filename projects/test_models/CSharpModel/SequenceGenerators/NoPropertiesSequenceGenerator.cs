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
using System.Collections.Generic;
using System.Collections;
using System;

namespace Dogen.TestModels.CSharpModel
{
    /// <summary>
    /// Generates sequences of NoProperties.
    /// </summary>
    public static class NoPropertiesSequenceGenerator
    {
		static internal NoProperties Create(uint position)
		{
			var result = new NoProperties();
			return result;
		}

		#region Enumerator
		private class NoPropertiesEnumerator : IEnumerator, IEnumerator<NoProperties>, IDisposable 
		{
			#region Properties
			private uint _position;
			private readonly NoProperties _current;
			#endregion

			#region IDisposable
			public void Dispose()
			{
			}
			#endregion

			#region IEnumerator implementation
			public bool MoveNext()
			{
				++_position;
				Create(_position);
				return true;
			}

			public void Reset()
			{
				_position = 0;
				Create(_position);
			}

			public object Current {
				get
				{
					return _current;
				}
			}

			NoProperties IEnumerator<NoProperties>.Current                                                
			{                                                                           
				get                                                                     
				{                                                                       
					return _current;                                           
				}                                                                       
			}                                                                           
			#endregion

			public NoPropertiesEnumerator()
			{
				_current = NoPropertiesSequenceGenerator.Create(_position);
			}
		}
		#endregion

		#region Enumerable
		private class NoPropertiesEnumerable : IEnumerable, IEnumerable<NoProperties>
		{
			#region IEnumerable implementation
			public IEnumerator GetEnumerator()
			{
				return new NoPropertiesEnumerator();
			}

			IEnumerator<NoProperties> IEnumerable<NoProperties>.GetEnumerator()
			{
				return new NoPropertiesEnumerator();
			}
			#endregion
		}
		#endregion

		static public IEnumerable<NoProperties> Sequence()
		{
			return new NoPropertiesEnumerable();
		}
	}
}

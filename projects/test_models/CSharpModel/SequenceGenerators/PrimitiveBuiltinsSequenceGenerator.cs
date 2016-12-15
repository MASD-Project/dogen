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
using System.Collections;
using System.Collections.Generic;

namespace Dogen.TestModels.CSharpModel
{
    /// <summary>
    /// Generates sequences of PrimitiveBuiltins.
    /// </summary>
	public static class PrimitiveBuiltinsSequenceGenerator {
		#region Factory methods
		static byte CreateByte(uint position)
		{
			return Convert.ToByte(position);
		}

		static sbyte CreateShortByte(uint position)
		{
			return Convert.ToSByte(position);
		}

		static int CreateInt(uint position)
		{
			return Convert.ToInt32(position);
		}

		static uint CreateUInt(uint position)
		{
			return position;
		}

		static short CreateShort(uint position)
		{
			return Convert.ToInt16(position);
		}

		static ushort CreateUShort(uint position)
		{
			return Convert.ToUInt16(position);
		}

		static long CreateLong(uint position)
		{
			return Convert.ToInt64(position);
		}

		static ulong CreateULong(uint position)
		{
			return Convert.ToUInt64(position);
		}

		static float CreateFloat(uint position)
		{
			return Convert.ToSingle(position);
		}

		static double CreateDouble(uint position)
		{
			return Convert.ToDouble(position);
		}

		static char CreateChar(uint position)
		{
			return Convert.ToChar(position);
		}

		static bool CreateBool(uint position)
		{
			return position % 2 == 0;
		}

		static decimal CreateDecimal(uint position)
		{
			return Convert.ToDecimal(position);
		}

		static internal PrimitiveBuiltins Create(uint position)
		{
			var result = new PrimitiveBuiltins();

			result.ByteProperty = CreateByte(position + 0);
			result.ShortByteProperty = CreateShortByte(position + 1);
			result.IntProperty = CreateInt(position + 2);
			result.UIntProperty = CreateUInt(position + 3);
			result.ShortProperty = CreateShort(position + 4);
			result.UShortProperty = CreateUShort(position + 5);
			result.LongProperty = CreateLong(position + 6);
			result.ULongProperty = CreateULong(position + 7);
			result.FloatPropertyOne = CreateFloat(position + 8);
			result.FloatPropertyTwo = CreateFloat(position + 9);
			result.DoublePropertyOne = CreateDouble(position + 10);
			result.DoublePropertyTwo = CreateDouble(position + 11);
			result.CharProperty = CreateChar(position + 12);
			result.BoolProperty = CreateBool(position + 13);
			result.DecimalProperty = CreateDecimal(position + 14);

			return result;
		}
		#endregion

		#region Enumerator
		private class PrimitiveBuiltinsEnumerator : IEnumerator, IEnumerator<PrimitiveBuiltins>, IDisposable 
		{
			#region Properties
			private uint _position;
			private readonly PrimitiveBuiltins _current;
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

			PrimitiveBuiltins IEnumerator<PrimitiveBuiltins>.Current                                                
			{                                                                           
				get                                                                     
				{                                                                       
					return _current;                                           
				}                                                                       
			}                                                                           
			#endregion

			public PrimitiveBuiltinsEnumerator()
			{
				_current = PrimitiveBuiltinsSequenceGenerator.Create(_position);
			}
		}
		#endregion

		#region Enumerable
		private class PrimitiveBuiltinsEnumerable : IEnumerable, IEnumerable<PrimitiveBuiltins>
		{
			#region IEnumerable implementation
			public IEnumerator GetEnumerator()
			{
				return new PrimitiveBuiltinsEnumerator();
			}

			IEnumerator<PrimitiveBuiltins> IEnumerable<PrimitiveBuiltins>.GetEnumerator()
			{
				return new PrimitiveBuiltinsEnumerator();
			}
			#endregion
		}
		#endregion

		static public IEnumerable<PrimitiveBuiltins> Sequence()
		{
			return new PrimitiveBuiltinsEnumerable();
		}
	}
}

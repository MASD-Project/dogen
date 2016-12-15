using System;

namespace Dogen.TestModels.CSharpModel
{
	static class GeneratorHelper
	{
		public static object CreateObject(uint position)
		{
			return "this is an object: " + Convert.ToString(position);
		}

		public static string CreateString(uint position)
		{
			return "this is a string: " + Convert.ToString(position);
		}

		public static byte CreateByte(uint position)
		{
			return Convert.ToByte(position);
		}

		public static sbyte CreateShortByte(uint position)
		{
			return Convert.ToSByte(position);
		}

		public static int CreateInt(uint position)
		{
			return Convert.ToInt32(position);
		}

		public static uint CreateUInt(uint position)
		{
			return position;
		}

		public static short CreateShort(uint position)
		{
			return Convert.ToInt16(position);
		}

		public static ushort CreateUShort(uint position)
		{
			return Convert.ToUInt16(position);
		}

		public static long CreateLong(uint position)
		{
			return Convert.ToInt64(position);
		}

		public static ulong CreateULong(uint position)
		{
			return Convert.ToUInt64(position);
		}

		public static float CreateFloat(uint position)
		{
			return Convert.ToSingle(position);
		}

		public static double CreateDouble(uint position)
		{
			return Convert.ToDouble(position);
		}

		public static char CreateChar(uint position)
		{
			return Convert.ToChar(position);
		}

		public static bool CreateBool(uint position)
		{
			return position % 2 == 0;
		}

		public static decimal CreateDecimal(uint position)
		{
			return Convert.ToDecimal(position);
		}
	}
}

